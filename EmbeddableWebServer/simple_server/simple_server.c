// simple_server.c 
// https://github.com/hellerf/EmbeddableWebServer

#include "EmbeddableWebServer.h"
#include "file_util.h"

int main(int argc, char* argv[]) {
	return acceptConnectionsUntilStoppedFromEverywhereIPv4(NULL, 8080);
}


struct Response* createResponseForRequest(const struct Request* request, struct Connection* connection) {
	if (0 == strcmp(request->pathDecoded, "/")) {
		char *file = "data/index.html";
		char error[100];
		char* html = file_text_read(file, error);
		return responseAllocHTML(html);
	}
	if (0 == strcmp(request->pathDecoded, "/welcome")) {
		return responseAllocHTML("<html><body><marquee><h1>Welcome to my home page</h1></marquee></body></html>");
	}
	if (0 == strcmp(request->pathDecoded, "/status/json")) {
		static const char* statuses[] = { ":-)", ":-(", ":-|" };
		int status = rand() % (sizeof(statuses) / sizeof(*statuses));
		/* There is also a family of responseAllocJSON functions */
		return responseAllocWithFormat(200, "OK", "application/json", "{ \"status\" : \"%s\" }", statuses[status]);
	}
	if (0 == strcmp(request->pathDecoded, "/100_random_numbers")) {
		struct Response* response = responseAllocHTML("<html><body><h1>100 Random Numbers</h1><ol>");
		for (int i = 1; i <= 100; i++) {
			heapStringAppendFormat(&response->body, "<li>%d</li>\n", rand());
		}
		heapStringAppendString(&response->body, "</ol></body></html>");
		return response;
	}
	/* Serve files from the current directory */
	if (request->pathDecoded == strstr(request->pathDecoded, "/files")) {
		return responseAllocServeFileFromRequestPath("/files", request->path, request->pathDecoded, ".");
	}
	return responseAlloc404NotFoundHTML("What?!");
}
