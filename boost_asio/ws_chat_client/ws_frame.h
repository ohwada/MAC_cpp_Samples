#pragma once
/**
 * ws_frame.h
 * 2022-10-01 K.OHWADA
 */


/**
 * control bit
 */
const unsigned char  B_FIN = 0x80;
const unsigned char  B_RSV1 = 0x40;
 const unsigned char  B_RSV2 = 0x20;
const unsigned char  B_RSV13 = 0x10;
const unsigned char  B_MASK = 0x80;


/**
 * bit mask
 */
const unsigned char  OPCODE_MASK = 0x0f;
const unsigned char  PAYLOAD_LEN_MASK = 0x7f;


/**
 * opcode
 */
typedef enum {
	OP_CONTINUATION = 0x00,
	OP_TEXT = 0x01,
	OP_BINARY = 0x02,
	OP_CLOSE = 0x08,
	OP_PING = 0x09,
	OP_PONG = 0x0A,
} opcode;


/**
 * size
 */
  const size_t FRAME_BASE_SIZE = 2;
  const size_t FRAME_MASK_SIZE = 4;
  const size_t FRAME_CLOSE_CODE_SIZE = 2;


/**
 * closecode
 */
typedef enum {
CLOSE_NORMAL = 1000,
CLOSE_GOING_AWAY = 1001,
CLOSE_PROTOCOL_ERROR = 1002,
CLOSE_UNKNOWN_DATA = 1003,
CLOSE_BAD_PAYLOAD = 1007,
CLOSE_POLICY_ERROR = 1008,
CLOSE_CLOSE_TOO_BIG = 1009,
CLOSE_NEEDS_EXTENSION = 1010,
CLOSE_INTERNAL_ERROR = 1011,
CLOSE_SERVICE_RESTART = 1012,
CLOSE_TRY_AGAIN_LATER = 1013,
} closecode;


// prototype
char* closecode_to_string(int code);


/**
 * closecode_to_string
 */
char* closecode_to_string(int code)
{
    if(code == CLOSE_NORMAL){
        return  (char *)"Close Normal";
    } else if(code == CLOSE_GOING_AWAY) {
        return  (char *)"Close Going_away";
    }else if(code == CLOSE_PROTOCOL_ERROR) {
        return (char *)"Close Protocol_error";
    }
        return (char *)"Close Unknown";
}


