// change log
// 2022-06-01 K.OHWADA
// int main()
// #include <string.h>

// original : https://github.com/kumagaihs/cmn-clib/blob/master/cmn-clib/test/src/test_CmnNet.c
/** @file
 * @brief CmnThreadライブラリの動作を確認するためのテストプログラム
 * @author H.Kumagai
 * @date 2020-07-30
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmnclib/CmnTest.h"
#include "cmnclib/CmnNet.h"

static void serverMethod(CmnNetSocket *socket)
{
	/* サーバー処理：データ受信してそのまま送り返す */
	CmnDataBuffer *request = CmnDataBuffer_Create(0);
	CmnNetSocket_ReceiveAll(socket, request, NULL, 0);
	CmnNetSocket_SendAll(socket, request->data, request->size);
}

static void test_CmnNetSocket_StartServer(CmnTestCase *t)
{
	// CmnNetSocketServer server, server2;
	CmnNetSocketServer server;
	CmnNetSocketStatus serverRet;
	unsigned short port = 44556;

	CmnDataBuffer *request, *response;
	char *requestData = "test data";

	/* サーバースタート */
	serverRet = CmnNetSocket_StartServer(port, serverMethod, &server);
	CmnTest_AssertNumber(t, __LINE__, serverRet, CNS_SUCCESS);

	/* Listenされるまで少しスリープ */
	CmnTime_Sleep(500);

	/* リクエスト送信（Graceful Close） */
	request = CmnDataBuffer_Create(0);
	response = CmnDataBuffer_Create(0);
	CmnDataBuffer_Append(request, requestData, strlen(requestData) + 1);
	CmnNetSocket_NoSessionRequest("127.0.0.1", port, request, response, NULL, 0, CNS_OPT_GRACEFUL_CLOSE);
	CmnTest_AssertData(t, __LINE__, request->data, response->data, strlen(requestData) + 1);

	/* リクエスト送信（end mark） */
/* TODO テスト不十分。以下実行するとrecvでブロックしてフリーズ状態になる。
	request = CmnDataBuffer_Create(0);
	response = CmnDataBuffer_Create(0);
	CmnDataBuffer_Append(request, requestData, strlen(requestData));
	CmnNetSocket_NoSessionRequest("localhost", port, request, response, "data", 4, 0);
	CmnTest_AssertData(t, __LINE__, request->data, response->data, strlen(requestData));
*/

	/* リクエスト処理されるまで少しスリープ */
	CmnTime_Sleep(1000);

	/* サーバー停止 */
	serverRet = CmnNetSocket_EndServer(&server);
	CmnTest_AssertNumber(t, __LINE__, serverRet, CNS_SUCCESS);

	/* サーバー停止まで待機 */
	CmnThread_Join(server.acceptThread);
}

void test_CmnNet_AddCase(CmnTestPlan *plan)
{
	CmnTest_AddTestCaseEasy(plan, test_CmnNetSocket_StartServer);
}


int main()
{
 	CmnTestPlan plan;
	CmnTest_InitializeTestPlan(&plan);

 	test_CmnNet_AddCase(&plan);

	return 0;
}