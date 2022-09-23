#include "mongoose.h"

static const char *user = "aaa@gmail.com";  // Change this! Your gmail account
static const char *pass = "xxxxxxxxxxxxx";  // Change this! Your gmail password
static const char *to = "bbb@gmail.com";    // Change this! Destination email

static const char *from = "My Mail Sender";
static const char *subj = "test email from mongoose library!";
static const char *mesg = "Hi!\nThis is a test message.\nBye.";

static bool s_quit;

enum { EHLO, STARTTLS, STARTTLS_WAIT, AUTH, FROM, TO, DATA, BODY, QUIT, END };

static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
  uint8_t *state = (uint8_t *) c->label;
  if (ev == MG_EV_OPEN) {
    // c->is_hexdumping = 1;
  } else if (ev == MG_EV_READ) {
    if (c->recv.len > 0 && c->recv.buf[c->recv.len - 1] == '\n') {
      MG_INFO(("<-- %.*s", (int) c->recv.len - 2, c->recv.buf));
      c->recv.len = 0;
      if (*state == EHLO) {
        mg_printf(c, "EHLO gmail.com\r\n");
        *state = c->is_tls ? AUTH : STARTTLS;
      } else if (*state == STARTTLS) {
        mg_printf(c, "STARTTLS\r\n");
        *state = STARTTLS_WAIT;
      } else if (*state == STARTTLS_WAIT) {
        struct mg_tls_opts opts = {.ca = "/tmp/ca.pem"};
        mg_tls_init(c, &opts);
        *state = EHLO;
      } else if (*state == AUTH) {
        char a[100], b[300] = "";
        size_t n = mg_snprintf(a, sizeof(a), "%c%s%c%s", 0, user, 0, pass);
        mg_base64_encode((uint8_t *) a, n, b);
        mg_printf(c, "AUTH PLAIN %s\r\n", b);
        *state = FROM;
      } else if (*state == FROM) {
        mg_printf(c, "MAIL FROM: <%s>\r\n", user);
        *state = TO;
      } else if (*state == TO) {
        mg_printf(c, "RCPT TO: <%s>\r\n", to);
        *state = DATA;
      } else if (*state == DATA) {
        mg_printf(c, "DATA\r\n");
        *state = BODY;
      } else if (*state == BODY) {
        mg_printf(c, "From: %s <%s>\r\n", from, user);  // Mail header
        mg_printf(c, "Subject: %s\r\n", subj);          // Mail header
        mg_printf(c, "\r\n");                           // End of headers
        mg_printf(c, "%s\r\n", mesg);                   // Mail body
        mg_printf(c, ".\r\n");                          // End of body
        *state = QUIT;
      } else if (*state == QUIT) {
        mg_printf(c, "QUIT\r\n");
        *state = END;
      } else {
        c->is_draining = 1;
        MG_INFO(("end"));
      }
      MG_INFO(("--> %.*s", (int) c->send.len - 2, c->send.buf));
    }
  } else if (ev == MG_EV_CLOSE) {
    s_quit = true;
  } else if (ev == MG_EV_TLS_HS) {
    MG_INFO(("TLS handshake done!"));
    mg_printf(c, "EHLO gmail.com\r\n");
  }
  (void) fn_data, (void) ev_data;
}

int main(void) {
  struct mg_mgr mgr;
  mg_mgr_init(&mgr);
  // mg_log_set(MG_LL_VERBOSE);
  mg_connect(&mgr, "tcp://smtp.gmail.com:587", fn, NULL);
  while (s_quit == false) mg_mgr_poll(&mgr, 1000);
  return 0;
}
