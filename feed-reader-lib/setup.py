#!/usr/bin/python

import subprocess, sys, os, argparse
from scripts.utils import Utils
from collections import namedtuple

BuildPaths = namedtuple("BuildPaths", 'url build_dir build_sub_dir local_dir')

def shellquote(s):
    # from http://stackoverflow.com/a/35857
    return "'" + s.replace("'", "'\\''") + "'"

class Paths():
    def __init__(self):
        self.base_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), "external"))
        self.ext_tars = os.path.join(self.base_dir, "tarballs")
        self.ext_build = os.path.join(self.base_dir, "build")
        self.install_dir = os.path.join(self.base_dir, "local")
        Utils.mkdir(self.ext_tars)
        Utils.mkdir(self.ext_build)
        self.paths = {}
        self.paths["zi_lib"] = self.__zi_lib()
        self.paths["cppitertools"] = self.__cppitertools()
        self.paths["boost"] = self.__boost()

    def path(self, name):
        if name in self.paths:
            return self.paths[name]
        raise Exception(name + " not found in paths")

    def __zi_lib(self):
        url = 'https://github.com/weng-lab/zi_lib.git'
        local_dir = os.path.join(self.install_dir, "zi_lib")
        return BuildPaths(url, '', '', local_dir)

    def __cppitertools(self):
        url = 'https://github.com/ryanhaining/cppitertools.git'
        local_dir = os.path.join(self.install_dir, "cppitertools")
        return BuildPaths(url, '', '', local_dir)

    def __boost(self):
        url = "http://downloads.sourceforge.net/project/boost/boost/1.55.0/boost_1_55_0.tar.gz"
        return self.__package_dirs(url, "boost")

    def __package_dirs(self, url, name):
        build_dir = os.path.join(self.ext_build, name)
        fn = os.path.basename(url)
        fn_noex = fn.replace(".tar.gz", "").replace(".tar.bz2", "")
        build_sub_dir = os.path.join(build_dir, fn_noex)
        local_dir = os.path.join(self.install_dir, name)
        return BuildPaths(url, build_dir, build_sub_dir, local_dir)

class Setup:
    def __init__(self, args):
        self.paths = Paths()
        self.args = args
        self.__processArgs()

    def __processArgs(self):
        dirs = self.args.dirsToDelete
        if not dirs:
            return

        if "all" == dirs[0]:
            dirs = []
            for k, _ in self.paths.paths.iteritems():
                dirs.append(k)

        if "shark" in dirs and not "boost149" in dirs:
            dirs.append("boost149")

        for e in dirs:
            p = self.__path(e)
            if p.build_dir:
                Utils.rm_rf(p.build_dir)
            if p.local_dir:
                Utils.rm_rf(p.local_dir)

    def __path(self, name):
        return self.paths.path(name)

    def __setup(self, name, builder_f):
        if os.path.exists(self.__path(name).local_dir):
            print name, "found"
        else:
            print name, "NOT found; building..."
            builder_f()

    def setup(self):
        self.__setup("zi_lib", self.zi_lib)
        self.__setup("cppitertools", self.cppitertools)
        self.__setup("boost", self.boost)

    def num_cores(self):
        c = Utils.num_cores()
        if c > 8:
            return 8
        if 1 == c:
            return 1
        return c - 1

    def __build(self, i, cmd):
        print "\t getting file..."
        fnp = Utils.get_file_if_size_diff(i.url, self.paths.ext_tars)
        Utils.clear_dir(i.build_dir)
        Utils.untar(fnp, i.build_dir)
        try:
            Utils.run_in_dir(cmd, i.build_sub_dir)
        except:
            Utils.rm_rf(i.local_dir)
            sys.exit(1)

    def boost(self):
        i = self.__path("boost")
        cmd = "./bootstrap.sh --prefix={local_dir} && ./b2 -j {num_cores} install".format(
            local_dir=shellquote(i.local_dir).replace(' ', '\ '), num_cores=self.num_cores())
        self.__build(i, cmd)

    def __git(self, i):
        cmd = "git clone {url} {d}".format(url=i.url, d=shellquote(i.local_dir))
        Utils.run(cmd)

    def zi_lib(self):
        self.__git(self.__path('zi_lib'))

    def cppitertools(self):
        self.__git(self.__path('cppitertools'))
        i = self.__path('cppitertools')
        cmd = "cd {d} && git checkout d4f79321842dd584f799a7d51d3e066a2cdb7cac".format(d=shellquote(i.local_dir))
        Utils.run(cmd)

    def ubuntu(self):
        pkgs = """libbz2-dev python2.7-dev cmake libpcre3-dev zlib1g-dev libgcrypt11-dev libicu-dev
python doxygen doxygen-gui auctex xindy graphviz libcurl4-openssl-dev""".split()

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('dirsToDelete', type=str, nargs='*')
    return parser.parse_args()

def main():
    args = parse_args()

    s = Setup(args)
    s.setup()
main()
