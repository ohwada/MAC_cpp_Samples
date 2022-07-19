#!/usr/bin/python

import urllib, os, shutil, tarfile, multiprocessing, subprocess, sys

class Utils:
    @staticmethod
    def run_in_dir(cmd, d):
        cmd = "cd " + Utils.shellquote(d) + " && " + cmd + " && cd -"
        Utils.run(cmd)

    @staticmethod
    def run(cmd):
        # from http://stackoverflow.com/a/4418193
        process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        # Poll process for new output until finished
        while True:
            nextline = process.stdout.readline()
            if nextline == '' and process.poll() != None:
                break
            sys.stdout.write(nextline)
            sys.stdout.flush()

        output = process.communicate()[0]
        exitCode = process.returncode

        if (exitCode == 0):
            return output
        raise Exception(cmd, exitCode, output)

    @staticmethod
    def shellquote(s):
        " from http://stackoverflow.com/a/35857"
        return "'" + s.replace("'", "'\\''") + "'"

    @staticmethod
    def num_cores():
        return multiprocessing.cpu_count()

    @staticmethod
    def mkdir(d):
        if not os.path.exists(d):
            print "mkdir", d
            os.makedirs(d)

    @staticmethod
    def get_file(url, d):
        fn = url.split('/')[-1]
        out_fnp = os.path.join(d, fn)
        urllib.urlretrieve(url, out_fnp)
        return out_fnp

    @staticmethod
    def get_file_if_size_diff(url, d):
        fn = url.split('/')[-1]
        out_fnp = os.path.join(d, fn)
        net_file_size = int(urllib.urlopen(url).info()['Content-Length'])
        if os.path.exists(out_fnp):
            fn_size = os.path.getsize(out_fnp)
            if fn_size == net_file_size:
                print "skipping download of", fn
                return out_fnp
            else:
                print "files sizes differed:", "on disk:", fn_size, "from net:", net_file_size
        print "retrieving", fn
        urllib.urlretrieve(url, out_fnp)
        return out_fnp

    @staticmethod
    def rm_rf(d):
        if os.path.exists(d):
            print "rm -rf", d
            shutil.rmtree(d)

    @staticmethod
    def untar(fnp, d):
        if fnp.endswith(".tar.gz"):
            tar = tarfile.open(fnp, "r:gz")
        elif fnp.endswith(".tar.bz2"):
            tar = tarfile.open(fnp, "r:bz2")
        elif fnp.endswith(".tar"):
            tar = tarfile.open(fnp, "r")
        else:
            raise Exception("invalid file? " + fnp)
        print "untarring", fnp, "to", d
        tar.extractall(d)
        tar.close()

    @staticmethod
    def clear_dir(d):
        Utils.rm_rf(d)
        Utils.mkdir(d)
