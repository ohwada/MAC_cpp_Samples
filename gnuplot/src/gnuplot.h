/**
 * gnuplot sample
 * 2020-03-01 K.OHWADA
 */

// modify for MAC
// original : https://gist.github.com/hecomi/b7d56d876335e67b6eaaa493dbf6f92e

/*! @file
 @brief		gnuplotクラス
 @author	hecomi (http://d.hatena.ne.jp/hecomi/)
 @date		December 09, 2010. ver. 1.03

 10/07/05 完成
 10/07/12 ログプロット/reset/PNG出力追加
 10/07/13 マルチプロット
 10/12/09 ヘッダファイルのみに変更
*/

#pragma once
#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#define __KEYWAIT__ { int i; std::cin >> i; } 

#ifdef USE_BOOST
#include <boost/multi_array.hpp>
#endif

namespace gnuplot {

/*!
@brief gnuplotを扱うライブラリ
	gnuplotを扱うクラスに関するライブラリです．
	pgnuplotへとパイプを繋ぎ，関数やデータをgnuplotを用いてプロットする手助けをします．
	pgnuplot.exeが環境変数に登録されている必要があります．
*/
class CGnuplot
{
private:
/* ----------------------------------------------------------------------
 プロットのスタイルを変更したい場合はここを変更
---------------------------------------------------------------------- */
	/*!
	@brief スタイル初期化
	*/
	void InitialStyle()
	{
		Command("set style line  1 linetype  1 linewidth 2");
		Command("set style line  2 linetype  2 linewidth 2");
		Command("set style line  3 linetype  3 linewidth 2");
		Command("set style line  4 linetype  4 linewidth 2");
		Command("set style line  5 linetype  5 linewidth 2");
		Command("set style line  6 linetype  6 linewidth 2");
		Command("set style line  7 linetype  7 linewidth 2");
		Command("set style line  8 linetype  8 linewidth 2");
		Command("set style line  9 linetype  9 linewidth 2");
		Command("set style line 10 linetype 10 linewidth 2");
	}

	/*!
	@brief スタイル初期化
	*/
	void OutputStyle()
	{
		Command("set style line  1 linetype  1 linewidth 6");
		Command("set style line  2 linetype  2 linewidth 6");
		Command("set style line  3 linetype  3 linewidth 6");
		Command("set style line  4 linetype  4 linewidth 6");
		Command("set style line  5 linetype  5 linewidth 6");
		Command("set style line  6 linetype  6 linewidth 6");
		Command("set style line  7 linetype  7 linewidth 6");
		Command("set style line  8 linetype  8 linewidth 6");
		Command("set style line  9 linetype  9 linewidth 6");
		Command("set style line 10 linetype 10 linewidth 6");
	}

/* ----------------------------------------------------------------------
 メンバ変数
---------------------------------------------------------------------- */
	//! プロットする要素の開始位置と終了位置
	FILE* Fp;

	//! @brief 一時ファイル名
	const std::string TempFileName;

	//! プロットする要素の開始位置と終了位置
	template <class Container>
	struct PlotInfo
	{
		Container begin;	//!< プロット開始位置
		Container end;		//!< プロット終了位置
	};

	//! マルチプロットかどうか
	bool IfMultiplot;

	//! プロットファイル用ナンバー初期値
	const unsigned int DefaultNo;

	//! プロットファイル用ナンバー（Temp(No).dat）
	unsigned int No;

	//! プロットファイル用ナンバーの最大値
	unsigned int MaxNo;

/* ----------------------------------------------------------------------
 内部で扱う関数達
---------------------------------------------------------------------- */
	//! ファイル名取得
	std::string GetPlotFileName()
	{
		std::stringstream ss;
		ss << TempFileName << No << ".dat";
		return ss.str();
	}

	/*!
	@brief 初期化
	*/
	void Ini()
	{
		//Fp = _popen("gnuplot", "w");
    	const char *CMD = "/usr/local/bin/gnuplot";
		Fp = popen(CMD, "w");

		if (Fp == NULL) {
			printf("pipe error\n");
			exit(EXIT_FAILURE);
		}
		InitialStyle();
	}

	/*!
	@brief バッファフラッシュ
	*/
	void Flush()
	{
		fflush(Fp);
	}

	/*!
	@brief プロットコマンド
	*/
	void Plot()
	{
		Command("plot '%s' w %s ls %d notitle", GetPlotFileName().c_str(), GetPlotType().c_str(), No);

		// マルチプロットの場合は番号をセット
		if (IfMultiplot) {
			No++;
			if (No > MaxNo) {
				MaxNo = No;
			}
		}
	}

	/*!
	@brief sプロットコマンド
	*/
	void SPlot(std::string option = "")
	{
		Command("set hidden3d");
		Command(("splot '%s' notitle " + option).c_str(), GetPlotFileName().c_str(), GetPlotType().c_str(), No);

		// マルチプロットの場合は番号をセット
		if (IfMultiplot) {
			No++;
			if (No > MaxNo) {
				MaxNo = No;
			}
		}
	}

	/*!
	@brief 1次元要素をプロットする
	@param[in] x プロット情報を格納したxデータ
	*/
	template <class T>
	void PlotX(PlotInfo<T> x)
	{
		T it = x.begin;
		std::ofstream fout(GetPlotFileName().c_str());
		if (fout.fail()) {
			std::cout << "Error! (@PlotX)" << std::endl;
			return;
		}
		while (it != x.end) {
			fout << *it << std::endl;
			it++;
		}
		Plot();
	}

	/*!
	@brief 2次元要素をプロットする
	@param[in] x プロット情報を格納したxデータ
	@param[in] y プロット情報を格納したyデータ
	*/
	template <class T>
	void PlotXY(PlotInfo<T> x, PlotInfo<T> y)
	{
		T itX = x.begin, itY = y.begin;
		std::ofstream fout(GetPlotFileName().c_str());
		if (fout.fail()) {
			std::cout << "Error! (@PlotXY)" << std::endl;
			return;
		}
		while (itX != x.end && itY != y.end) {
			fout << *itX << " " << *itY << std::endl;
			itX++; itY++;
		}
		Plot();
	}

	/*!
	@brief 3次元要素をプロットする
	@param[in] x プロット情報を格納したxデータ
	@param[in] y プロット情報を格納したyデータ
	@param[in] z プロット情報を格納したzデータ
	*/
	template <class T>
	void PlotXYZ(PlotInfo<T> x, PlotInfo<T> y, PlotInfo<T> z)
	{
		T itX = x.begin, itY = y.begin, itZ = z.begin;
		std::ofstream fout(GetPlotFileName().c_str());
		if (fout.fail()) {
			std::cout << "Error! (@PlotXYZ)" << std::endl;
			return;
		}
		while (itX != x.end && itY != y.end && itZ != z.end) {
			fout << *itX << " " << *itY << " " << *itZ << std::endl;
			itX++; itY++; itZ++;
		}
		SPlot();
	}

	/*!
	@brief プロットタイプに応じた文字列を取得
	*/
	std::string GetPlotType()
	{
		switch (PlotType) {
			case PLOT_TYPE_LINES:			return "lines";			break;
			case PLOT_TYPE_POINTS:			return "points";		break;
			case PLOT_TYPE_LINES_POINTS:	return "linespoints";	break;
			default:						return "lines";
		}
	}


public:
	/*! @brief コンストラクタ */
	CGnuplot() :
		TempFileName("Temp"),
		PlotType(PLOT_TYPE_LINES),
		IfMultiplot(false),
		DefaultNo(1),
		No(DefaultNo),
		MaxNo(DefaultNo)
	{
		Ini();
	}

	/*!
	@brief コンストラクタ
	複数のGnuplotを起動した際に，同名のプロットデータファイルが衝突すると，
	所望のプロット結果が得られないので，プロットデータファイル名を指定しなければならない．
	@param[in] fileName プロット時に生成するデータファイルの名前
	*/
	CGnuplot(const char* fileName) :
		TempFileName(fileName),
		PlotType(PLOT_TYPE_LINES),
		IfMultiplot(false),
		DefaultNo(1),
		No(DefaultNo),
		MaxNo(DefaultNo)
	{
		Ini();
	}

	/*! @brief デストラクタ */
	~CGnuplot()
	{
		Command("exit");

		// プロットファイルの削除
		for (No=DefaultNo; No<=MaxNo; No++) {
			remove(GetPlotFileName().c_str());
		}

		// _pclose(Fp);
		pclose(Fp);
	}

	/*! @brief 正常に機能しているかどうか */
	bool Check()
	{
		if (Fp == NULL) {
			return false;
		}
		return true;
	}
	
	/*!
	@brief printfライクにgnuplotのコマンドを実行
	@param[in] format printfに用いるフォーマット
	@param[in] ... 可変長引数
	*/
	void Command(const char* format, ...)
	{
		char buf[1024];
		va_list ap;

		va_start(ap, format);
		vsprintf(buf, format, ap);
		va_end(ap);

		fprintf(Fp, "%s\n", buf);
		Flush();
	}

	/*!
	@brief 関数をプロット
	Ex. DrawFunc("sin (x)")
	@param[in] format プロット対称関数文字列
	*/
	void DrawFunc(const char* func)
	{
		Command("plot %s", func);
	}

	/*!
	@brief 1次元要素をプロットする
	@param[in] cont プロット対称コンテナ
	*/
	template <class T, template <class A, class Allocator = std::allocator<A> > class Container>
	void Plot(Container<T> cont)
	{
		PlotInfo<typename Container<T>::iterator> pi = { cont.begin(), cont.end() };
		PlotX(pi);
	}

	/*!
	@brief 1次元要素をプロットする（配列）
	@param[in] cont プロット対称配列
	*/
	template <class T, int N>
	void Plot(T (&cont)[N])
	{
		PlotInfo<T*> pi = { &cont[0], &cont[N-1] };
		PlotX(pi);
	}

	/*!
	@brief 2次元要素をプロットする
	@param[in] contX プロット対称コンテナ（x）
	@param[in] contY プロット対称コンテナ（y）
	*/
	template <class T, template <class A, class Allocator = std::allocator<A> > class Container>
	void Plot(Container<T> contX, Container<T> contY)
	{
		PlotInfo<typename Container<T>::iterator> 
			piX = { contX.begin(), contX.end() },
			piY = { contY.begin(), contY.end() };
		PlotXY(piX, piY);
	}

	/*!
	@brief 2次元要素をプロットする（配列）
	@param[in] contX プロット対称配列（x）
	@param[in] contY プロット対称配列（y）
	*/
	template <class T, int N, int M>
	void Plot(T (&contX)[N], T (&contY)[M])
	{
		PlotInfo<T*> 
			piX = { &contX[0], &contX[N] },
			piY = { &contY[0], &contY[M] };
		PlotXY(piX, piY);
	}

	/*!
	@brief 3次元要素をプロットする
	@param[in] contX プロット対称コンテナ（x）
	@param[in] contY プロット対称コンテナ（y）
	@param[in] contZ プロット対称コンテナ（z）
	*/
	template <class T, template <class A, class Allocator = std::allocator<A> > class Container>
	void Plot(Container<T> contX, Container<T> contY, Container<T> contZ)
	{
		PlotInfo<typename Container<T>::iterator> 
			piX = { contX.begin(), contX.end() },
			piY = { contY.begin(), contY.end() },
			piZ = { contZ.begin(), contZ.end() };
		PlotXYZ(piX, piY, piZ);
	}

	/*!
	@brief 3次元要素をプロットする（配列）
	@param[in] contX プロット対称配列（x）
	@param[in] contY プロット対称配列（y）
	@param[in] contZ プロット対称配列（z）
	*/
	template <class T, int N, int M, int L>
	void Plot(T (&contX)[N], T (&contY)[M], T (&contZ)[L])
	{
		PlotInfo<T*> 
			piX = { &contX[0], &contX[N] },
			piY = { &contY[0], &contY[M] },
			piZ = { &contZ[0], &contZ[L] };
		PlotXYZ(piX, piY, piZ);
	}

	/*!
	@brief 2次元マルチプロット（STLコンテナ限定）（x軸共通）
	@param[in] x プロット用x軸ベクトル
	@param[in] ys yベクトルの集合
	*/
	template <class T, template <class A, class Allocator = std::allocator<A> > class Container>
	void Multiplot(Container<T> x, Container<std::pair<std::string, Container<T> > > ys)
	{
		// 念のため
		No = DefaultNo;

		// プロット開始
		Command("plot \\");

		// ファイルへ書き出し
		std::ofstream fout(GetPlotFileName().c_str());
		if (fout.fail()) {
			std::cout << "Error! (@Multiplot)" << std::endl;
			return;
		}

		// 第2引数の展開
		typename Container<std::pair<std::string, Container<T> > >::iterator itYs = ys.begin();
		unsigned int i = 1;
		while (itYs != ys.end()) {
			// ペアの展開
			std::pair<std::string, Container<T> > pair = *itYs;
			std::string title = pair.first;
			Container<T> y = pair.second;

			// イテレータ指定
			typename Container<T>::iterator itX = x.begin(), itY = y.begin();

			while (itX != x.end() && itY != y.end()) {
				fout << *itX << " " << *itY << std::endl;
				itX++; itY++;
			}
			fout << std::endl << std::endl;

			// プロット
			Command("'%s' ind %d w %s ls %d ti '%s'\\", GetPlotFileName().c_str(), i-1, GetPlotType().c_str(), i, title.c_str());
			if (i < ys.size()) {
				Command(",\\");
			} else {
				Command("");
				break;
			}

			itYs++;
			i++;
		}
	}

	/*!
	@brief 2次元マルチプロット（STLコンテナ限定）（x軸別）
	@param[in] plot プロットデータ
	*/
	template <class T, template <class A, class Allocator = std::allocator<A> > class Container>
	void Multiplot(Container<std::pair<std::string, std::pair<Container<T>, Container<T> > > > plot)
	{
		// 念のため
		No = DefaultNo;

		// プロット開始
		Command("plot \\");

		// ファイルへ書き出し
		std::ofstream fout(GetPlotFileName().c_str());
		if (fout.fail()) {
			std::cout << "Error! (@Multiplot)" << std::endl;
			return;
		}

		// 第2引数の展開
		typename Container<std::pair<std::string, std::pair<Container<T>, Container<T> > > >::iterator it = plot.begin();
		unsigned int i = 1;
		while (it != plot.end()) {
			// ペアの展開
			std::pair<std::string, std::pair<Container<T>, Container<T> > > pair = *it;
			std::string title = pair.first;
			Container<T> x = pair.second.first;
			Container<T> y = pair.second.second;

			// イテレータ指定
			typename Container<T>::iterator itX = x.begin(), itY = y.begin();

			while (itX != x.end() && itY != y.end()) {
				fout << *itX << " " << *itY << std::endl;
				itX++; itY++;
			}
			fout << std::endl << std::endl;

			// プロット
			Command("'%s' ind %d w %s ls %d ti '%s'\\", GetPlotFileName().c_str(), i-1, GetPlotType().c_str(), i, title.c_str());
			if (i < plot.size()) {
				Command(",\\");
			} else {
				Command("");
				break;
			}

			it++;
			i++;
		}
	}

/* ----------------------------------------------------------------------
 boost::multi_array で3Dプロットできます．
 使う際はUSE_BOOSTをdefineしてください．
---------------------------------------------------------------------- */
#ifdef USE_BOOST
	/*!
	@brief 3次元要素をプロットする（平面）
	@param[in] contX プロット対称コンテナ（x）
	@param[in] contY プロット対称コンテナ（y）
	@param[in] contZ プロット対称コンテナ（z）
	*/
	template <class T, template <class A, class Allocator = std::allocator<A> > class Container>
	void Plot(Container<T> contX, Container<T> contY, boost::multi_array<T, 2> contZ)
	{
		// プロットサイズ
		const int nX = contX.size();
		const int nY = contY.size();

		// ファイルへ書き出し
		std::ofstream fout(GetPlotFileName().c_str());
		if (fout.fail()) {
			std::cout << "Error! (@Plot)" << std::endl;
			return;
		}

		for (int i=0; i<nX; i++) {
			for (int j=0; j<nY; j++) {
				fout << contX[i] << " " << contY[j] << " " << contZ[i][j] << std::endl;
			}
			fout << std::endl;
		}

		SPlot("with pm3d");
	}
#endif

	/*!
	@brief 3次元要素をプロットする（平面）
	@param[in] contX プロット対称コンテナ（x）
	@param[in] contY プロット対称コンテナ（y）
	@param[in] contZ プロット対称コンテナ（z）
	*/
	template <class T, template <class A, class Allocator = std::allocator<A> > class Container>
	void Plot(Container<T> contX, Container<T> contY, Container<Container<T> > contZ)
	{
		// プロットサイズ
		const int nX = contX.size();
		const int nY = contY.size();

		// ファイルへ書き出し
		std::ofstream fout(GetPlotFileName().c_str());
		if (fout.fail()) {
			std::cout << "Error! (@Plot)" << std::endl;
			return;
		}

		for (int i=0; i<nX; i++) {
			for (int j=0; j<nY; j++) {
				fout << contX[i] << " " << contY[j] << " " << contZ[i][j] << std::endl;
			}
			fout << std::endl;
		}

		SPlot("with pm3d");
	}

	/*!
	@brief プロットタイプ
		PLOT_TYPE_LINES			線のみ
		PLOT_TYPE_POINTS		点のみ
		PLOT_TYPE_LINES_POINTS	線と点
	*/
	enum PLOT_TYPE {
		PLOT_TYPE_LINES,
		PLOT_TYPE_POINTS,
		PLOT_TYPE_LINES_POINTS
	} PlotType;

	/*!
	@brief プロットタイプ（線，点，線と点）をセット
	*/
	void SetPlotType(const PLOT_TYPE pt)
	{
		PlotType = pt;
	}

	/*!
	@brief マルチプロット（複数の図をプロット）の切り替え
	@param[in] sw true: マルチプロット false: 解除
	*/
	void SetMultiplot(const bool sw = true)
	{
		if (sw) {
			Command("set multiplot");
			IfMultiplot = true;

		} else {
			Command("unset multiplot");
			IfMultiplot = false;
			No = DefaultNo;
		}
	}

	/*!
	@brief ラベルをセット
	@param[in] title タイトル
	*/
	void SetTitle(const char* title)
	{
		Command("set title '%s'", title);
	}

	/*!
	@brief ラベルをセット
	@param[in] labelX Xラベル名
	@param[in] labelY Yラベル名
	*/
	void SetLabel(const char* labelX, const char* labelY)
	{
		Command("set xlabel '%s'", labelX);
		Command("set ylabel '%s'", labelY);
	}

	/*!
	@brief プロット範囲を指定
	@param[in] min x軸プロット範囲最小値
	@param[in] min y軸プロット範囲最小値
	*/
	void SetXRange(const double min, const double max)
	{
		Command("set xrange [%f:%f]", min, max);
	}

	/*!
	@brief プロット範囲を指定
	@param[in] min y軸プロット範囲最小値
	@param[in] min y軸プロット範囲最小値
	*/
	void SetYRange(const double min, const double max)
	{
		Command("set yrange [%f:%f]", min, max);
	}

	/*!
	@brief リプロット
	*/
	void Replot()
	{
		Command("replot");
	}

	/*!
	@brief 設定全リセット
	*/
	void Reset()
	{
		Command("reset");
	}

	/*!
	@brief 片対数プロットに変更
	*/
	void SetLogPlotY(const bool sw = true)
	{
		if (sw) {
			Command("set logscale y");
			Command("set format y \"10^{%%L}\"");
		} else {
			Command("set nolog y");
			Command("set format y");
		}
	}

	/*!
	@brief 逆片対数プロットに変更
	*/
	void SetLogPlotX(const bool sw = true)
	{
		if (sw) {
			Command("set logscale x");
			Command("set format x \"10^{%%L}\"");
		} else {
			Command("set nolog x");
			Command("set format x");
		}
	}

	/*!
	@brief 両対数プロットに変更
	*/
	void SetLogPlot(const bool sw = true)
	{
		SetLogPlotY(sw);
		SetLogPlotX(sw);
	}

	/*!
	@brief 現在プロットしているデータをファイルに書き出す
	中身はTempFileNameに保存されているデータをコピーしているだけ
	@param[in] fileName 書き出し先ファイル名
	*/
	void DumpToFile(const char* fileName)
	{
		std::ofstream fout(fileName, std::ios_base::binary);
		std::ifstream fin(GetPlotFileName().c_str(), std::ios_base::binary);
		if (fin.fail() || fout.fail()) {
			std::cout << "Error! (@DumpToFile)" << std::endl;
			return;
		}
		while (!fin.eof()) {
			const int BUF_SIZE = 4096;
			char buf[BUF_SIZE];
			fin.read(buf, BUF_SIZE);
			fout.write(buf, BUF_SIZE);
		}
	}

	/*!
	@brief 現在プロットしているデータをEPSで書き出す
	@param[in] fileName 書き出し先ファイル名
	*/
	void DumpToEps(const char* fileName)
	{
		OutputStyle();
		Command("set term postscript eps enhanced color \"Tahoma\" 35");
		Command("set output '%s.eps'", fileName);
		Command("set size 1.6,1.6");
		Command("set ticscale 3");
		Command("replot");
		Command("set output");
		Command("set terminal window");
		Command("set ticscale");
		Command("set size");
		InitialStyle();
	}

	/*!
	@brief 現在プロットしているデータをPNGで書き出す
	@param[in] fileName 書き出し先ファイル名
	*/
	void DumpToPng(const char* fileName)
	{
		Command("set term png");
		Command("set output '%s.png'", fileName);
		Command("set size");
		Command("set ticscale 3");
		Command("replot");
		Command("set output");
		Command("set terminal window");
		Command("set ticscale");
		InitialStyle();
	}

	/*!
	@brief 外部ファイルからコマンドを読み込み実行
	@param[in] fileName 読み込み元ファイル名
	*/
	void CommandFromFile(const char* fileName)
	{
		std::ifstream fin(fileName);
		if (fin.fail()) {
			std::cout << "Error! '" << fileName << "' is not found. (@CommandFromFile)" << std::endl;
			return;
		}
		std::string str;
		while (!fin.eof()) {
			std::getline(fin, str);
			Command(str.c_str());
		}
	}

};


/* ----------------------------------------------------------------------
 よく使うと思われる型
---------------------------------------------------------------------- */
/*! @brief xベクトル固定プロットの要素 */
typedef std::pair<std::string, std::vector<double> > StrVec;

/*! @brief xベクトル固定プロットの引数の型 */
typedef std::vector<std::pair<std::string, std::vector<double> > > SemiMultiPlot;

/*! @brief xベクトル可変プロットの要素 */
typedef std::pair<std::string, std::pair<std::vector<double>, std::vector<double> > > StrVecVec;

/*! @brief xベクトル可変プロット */
typedef std::vector<std::pair<std::string, std::pair<std::vector<double>, std::vector<double> > > > MultiPlot;


/* ----------------------------------------------------------------------
 これらの型を返す関数
---------------------------------------------------------------------- */
static StrVecVec svv(const std::string str, const std::vector<double> vecX, const std::vector<double> vecY)
{
	return StrVecVec(str, make_pair(vecX, vecY));
}


}