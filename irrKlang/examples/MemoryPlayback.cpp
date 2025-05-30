/**
 * irrKlang Sample
 * 2020-03-01 K.OHWADA
 */

// play from memory
// say okay
// original : http://www.ambiera.at/downloads/irrKlang-64bit-1.6.0.zip

// This example will show how to play sounds directly from memory using irrKlang.
// This is useful for embedding sounds directly in executables as well for
// making irrKlang work together with different APIs like advanced decoders or
// middleware such as Shockwave.

// lets start: include irrKlang headers and other input/output stuff
// needed to print and get user input from the console.

#include <stdio.h>
#include <irrKlang.h>
using namespace irrklang;

// include console I/O methods (conio.h for windows, our wrapper in linux)
#if defined(WIN32)
#include <conio.h>
#else
//#include "../common/conio.h"
#include "conio.h"
#endif

//#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

// the following huge array simply represents the plain sound data we
// want to play back. It is just the content of a .wav file from the
// game 'Hell Troopers'. Usually this sound is somewhere provided by
// some external software, but to keep it simple we just use this array as memory.

// test.wav, converted to this array by bin2h tool, available at bin2h.irrlicht3d.org
int memorySoundDataSize = 3932; // data size in bytes
int memorySoundData[] = {
	0x46464952, 0xf54, 0x45564157, 0x20746d66, 0x12,
	0x10001, 0x1f40, 0x1f40, 0x80001, 0x61660000, 0x47463,
	0xf220000,  0x61640000, 0xf226174,  0x807f0000, 0x80807f7f, 0x7f808080,
	0x80818080, 0x7f7f7e80, 0x7f807f7f, 0x80808081, 0x7e7e7e80, 0x807e7e7e,
	0x7f7f7f7f, 0x7e7e7f7f, 0x7f7e7e7e, 0x807f8080, 0x8181807f, 0x80808180,
	0x80808080, 0x83818181, 0x87868584, 0x85878786, 0x4f5a7183, 0x8a816d6e,
	0x97918f8c, 0x5f6e7684, 0x85837768, 0x95949089, 0x6b707b8f, 0x83807672,
	0x908f8c84, 0x6f727f87, 0x7d7b7770, 0x87858482, 0x76797e86, 0x807e7977,
	0x8987857f, 0x7b7c8085, 0x837f7f7b, 0x888a8884, 0x7d7c7d85, 0x948b8380,
	0x318da69d, 0x92735250, 0xbb818f7e, 0x5b879fb8, 0x805f4c45, 0x978f8a7c,
	0x6a95a8a7, 0x7863575b, 0x95878483, 0x81929a9a, 0x75655f60, 0x8283847f,
	0x7b8c918e, 0x7b706a73, 0x88878886, 0x80878987, 0x7e757475, 0x84848684,
	0x7c838384, 0x867e7a78, 0x93949390, 0x3c5e879b, 0x98493e3b, 0xab9d9d99,
	0x518e97a0, 0x6f58493e, 0xa09da799, 0x808a95a2, 0x705d505a, 0x949d9b7e,
	0x7b84868a, 0x695d5f71, 0x91999688, 0x81807e88, 0x87828080, 0xa7a29d8f,
	0x3131aead, 0x87783147, 0xc1baabbc, 0x319db2a3, 0x5f523139, 0xb7a4b281,
	0x809b9aab, 0x513e376a, 0xadb0986b, 0x7c8f95aa, 0x53536c7e, 0xa4917764,
	0x707d97a1, 0x76717370, 0x948b7977, 0x74869097, 0x7d79706d, 0x92898786,
	0xa09d9c98, 0x31a2b3a7, 0x7f573150, 0xc2a1c0b7, 0x4a65b39f, 0x31333166,
	0xc0c6a1a0, 0x7ca5a0b9, 0x31465271, 0xc68e8342, 0x7078a9b7, 0x6e70616d,
	0x8e827b6d, 0x7c939f96, 0xa290797e, 0x97bdb8aa, 0x31313136, 0xaaa06b47,
	0xc1adbfc6, 0x316b6db0, 0x7e6e3131, 0xbdbcc5c0, 0x6e7e91af, 0x543c3645,
	0xbeb58f65, 0x5a7897ae, 0x796e5a5b, 0x9f93887e, 0x7989a0a0, 0xb0847b77,
	0x43a0c2be, 0x44313145, 0xbdafa569, 0x89c6a59f, 0x3131429d, 0xba644731,
	0xa4c1bec7, 0x63848a96, 0x40364255, 0xb2ae7d6b, 0x959da7b2, 0x5f607b7d,
	0x99806b62, 0xb5c3c3c4, 0x3131417b, 0xa4843931, 0xc6bdbdbb, 0x456faab0,
	0x31313131, 0xc6c4aa86, 0x85a8b6c3, 0x313e6476, 0xa3523731, 0xc1c5c6c3,
	0x657685b5, 0x8b796562, 0x8789b3a3, 0x4537313a, 0x92998760, 0xa38cb09d,
	0x4f737c87, 0x75654145, 0xaaa7b29f, 0x7b8394a0, 0x4f5a5967, 0xa2916957,
	0x9dafbabc, 0x9d928a93, 0x315a7fb3, 0x60313131, 0xb6c4c2b2, 0x92897bbc,
	0x33586a6b, 0x846e4d31, 0xb2c4c4c9, 0x5b657398, 0x58625658, 0xb89a8866,
	0xadbec5c3, 0x6a84a6ac, 0x31313131, 0xc7ab8331, 0xa9b8c6c3, 0x5566699b,
	0x3c313138, 0xc5b8a24f, 0x87a3c5c3, 0x58535274, 0x7b705f57, 0xc4c2b68f,
	0x8399c3c4, 0x3131315a, 0xb99a4a31, 0xc3c1c8b8, 0x6a90b1c0, 0x31313148,
	0xb89a6133, 0xb0c4c6c6, 0x6e7c97a1, 0x66535463, 0xc6c5947b, 0x314f97c4,
	0x5f313131, 0xaaa08a7a, 0xb6b5af9d, 0x52738fba, 0x573f3131, 0xaba99c69,
	0xa4a6a7ac, 0x838a94a5, 0xa58a716e, 0x7299adaf, 0x45313131, 0xc6bfaa69,
	0x7a859cb3, 0x80868a74, 0x4141586e, 0xad8e734c, 0x8994afb0, 0x91898184,
	0x8d8b9495, 0x9ab0a799, 0x31316888, 0x94553831, 0xa8b4b7aa, 0x8c8a8a9a,
	0x5e6f878c, 0x5b3e3c3f, 0xb0a88870, 0x99a4aab1, 0xa09b9597, 0x87acacac,
	0x3131576e, 0x8a553a31, 0xb1b5aba0, 0x8d959c9f, 0x5f6b7887, 0x55444247,
	0xa2958764, 0xa5aeb1b0, 0x9f9b9aa1, 0x9eafada8, 0x31395485, 0x75403131,
	0xb3b3af92, 0x878e969d, 0x727b8186, 0x4847505d, 0x92806f52, 0xa5a9ada6,
	0x9a97979f, 0xaab0a8a4, 0x405c719f, 0x4d363131, 0x9f958f66, 0x8a8f8f98,
	0x8694908f, 0x5457757b, 0x7e5b574e, 0xb1ad9a8a, 0x9aa3a7af, 0x9f9d9b9a,
	0x4f77849f, 0x31313341, 0x947d6346, 0x929f98a2, 0x8184848a, 0x7c7e8382,
	0x6e656a6e, 0xb0a38675, 0x91acb5b9, 0x77757b85, 0x838b8c84, 0x4a4e6673,
	0x83665b4f, 0x888e928b, 0x7e757679, 0x92939186, 0x6b767e86, 0x8980766b,
	0x909b9d9a, 0x6e717586, 0x8c807874, 0x848b8f91, 0x75727579, 0x87848178,
	0x787a8284, 0x7e7b7876, 0x83868684, 0x78797a81, 0x86837d7a, 0x83868888,
	0x7c7a7c7e, 0x8483827e, 0x7e808384, 0x7f7d7d7d, 0x7e7f8081, 0x7978797c,
	0x817f7e7c, 0x7d7e8080, 0x817e7e7d, 0x81828282, 0x7e7d7d80, 0x8383817f,
	0x7f818384, 0x7e7e7d7e, 0x80818180, 0x7e7e7e7e, 0x81807f7e, 0x7f7e8080,
	0x817f807e, 0x81828282, 0x7c7d7e80, 0x8281807d, 0x80818182, 0x80818080,
	0x7d7e7f80, 0x7e7c7c7d, 0x8181807f, 0x80808081, 0x81818080, 0x7e808181,
	0x7e7e7d7e, 0x807f7f7e, 0x81808080, 0x80808180, 0x7f7f8080, 0x7e7e7e7e,
	0x7f7e7e7e, 0x807f807f, 0x81808080, 0x7e808181, 0x7c7c7e7e, 0x807e7e7d,
	0x80808080, 0x80808080, 0x7e7e8080, 0x7e7e7e7e, 0x7f7f7e7e, 0x80807f7f,
	0x80808080, 0x80818080, 0x7e7e8080, 0x7e7e7e7d, 0x7e7e7f7f, 0x8080807f,
	0x80808080, 0x807f8080, 0x807f7e7f, 0x7f7f7f7f, 0x807f807f, 0x8180807f,
	0x807f8080, 0x7e7e7e7d, 0x80807f7e, 0x81808080, 0x7f808080, 0x7e7f7f7f,
	0x80807f7f, 0x7f7f8080, 0x7f807f7e, 0x80808080, 0x7e808080, 0x7e7e7e7e,
	0x8080807f, 0x7f808080, 0x7e7f7f7f, 0x80807f80, 0x7f807f80, 0x807f807f,
	0x80808080, 0x7f7f7f7f, 0x8080807f, 0x7f7f7f7f, 0x807f807f, 0x80808080,
	0x7f808080, 0x7f807e7f, 0x80808080, 0x7f7f7e7f, 0x807f8080, 0x80808080,
	0x80807f80, 0x7f7f7e7f, 0x7f7f7f7f, 0x80808080, 0x80808080, 0x7e7e7e7f,
	0x7f7e7e7f, 0x7e7f7f80, 0x80807f7f, 0x807f7f7f, 0x807f8080, 0x7f7f7f80,
	0x80807e7e, 0x81808080, 0x7f7f8080, 0x7e7e7e7e, 0x945f7880, 0x787c908a,
	0x89aaa75b, 0xa17f6868, 0x43617b95, 0x76aeaa97, 0x97ac5b4e, 0x886e4f76,
	0x31889099, 0x86acbb7a, 0x98a96e6e, 0x7152457c, 0x7d8a9eab, 0x8a979086,
	0x8c57515f, 0x8f7c8380, 0x858e9994, 0x81858780, 0x6487877c, 0x78756d6a,
	0x927c8774, 0x91899689, 0x7b718786, 0x66766780, 0x797d756d, 0x9c938f83,
	0x7b7c828d, 0x7973737f, 0x8c7a8070, 0x8383847a, 0x8b8c8384, 0x6b898079,
	0x7d817c79, 0x848f8681, 0x89949187, 0x8691887e, 0x80817e87, 0x817b7886,
	0x7578707a, 0x776a666d, 0x867d7978, 0x97918e8a, 0x979d9491, 0xa2999c96,
	0x476cb0a4, 0x38505d80, 0x6b565862, 0x887e7c7b, 0x596a7975, 0x686d7052,
	0xa4afac7f, 0xb3bdc3c0, 0x73bcc3bd, 0x31527b67, 0x604d5a31, 0xa19e9587,
	0x76818699, 0x3e4b3e47, 0x9a876d4a, 0xc3bbc1c8, 0xc3bebfc3, 0x3889317e,
	0x70513131, 0xb7ada777, 0x717cb6b5, 0x42315a77, 0x714a3146, 0xc1c99f99,
	0xbec5c3c7, 0x3131c4b7, 0x31313145, 0xc8b3847e, 0x93c0c1bc, 0x314a5960,
	0x45473a31, 0xbab98f71, 0xc3c5c3c2, 0xbfbeb7c3, 0x31683165, 0x8fb33131,
	0xbfc5bab5, 0x52348ec1, 0x5f313131, 0xad976a5a, 0xc4c3c6c1, 0xb0b0c3c3,
	0x6a3175c0, 0x73313149, 0xbfcdb595, 0x3f8ebebb, 0x31313f47, 0x8c7b603f,
	0xbebeb9aa, 0xaebfc3c2, 0x3173bfad, 0x3131335b, 0xc9c09d7a, 0x79b6baba,
	0x31373f31, 0x8c765231, 0xbbb2a7ac, 0xc0c2b1ad, 0x5fc3abbd, 0x31393131,
	0xc0b28e31, 0xc2b5bac9, 0x313131b3, 0x78603131, 0xbaacab82, 0xc5b8abb9,
	0xc5adbbbe, 0x594131a7, 0xa54b3131, 0xb6bccca8, 0x313c95c1, 0x4c313139,
	0xa5ad8c85, 0x9cabafad, 0xafbfc0c3, 0x31315dc1, 0x8e313131, 0xbac6c6aa,
	0x31abc6b3, 0x31313131, 0xba908165, 0xa1b4b2a8, 0xb3c3b69c, 0x31a1c1bb,
	0x3131545e, 0xccaa9b53, 0x86c0b0b6, 0x31383935, 0x99805635, 0xaea89fb2,
	0xc0c69da5, 0x9dc3b1c2, 0x31315231, 0xb39da431, 0xc2bfbebe, 0x313a3185,
	0x87733331, 0xb5a4af9d, 0xc2b39fa5, 0xa3beb2bf, 0x315f3131, 0xaaa25131,
	0xc1b3becb, 0x3e3135c3, 0x724d3131, 0xb8a9ad9b, 0xbea6acc1, 0xb8bbb8bd,
	0x316d316b, 0x9b7f3131, 0xbac3c8c0, 0x3f3161b1, 0x63343131, 0xb0b5aa8d,
	0xa499a5bd, 0xc3b2b7c5, 0x645f31a1, 0x8f543131, 0xbcc2bfa5, 0x443a8fc3,
	0x4f31313a, 0xaead9b81, 0x9ba9b6be, 0xc8a5b1b9, 0x9d4c31b5, 0x94993131,
	0xbbb8c584, 0x4d31a5c7, 0x40313154, 0xb2a48f78, 0xa5acbdc1, 0xc5afa7b6,
	0xb16231b8, 0x90b23131, 0xb9b3c176, 0x5d319dca, 0x7031315f, 0xacaa8c76,
	0xacaabbbd, 0xc7abaac3, 0x318331ad, 0x79bd3131, 0xc0b3ba83, 0x6c3187c6,
	0x73313152, 0xb2af9177, 0xb1a3a7c5, 0x91ba9ea9, 0x3175a831, 0xa4b98131,
	0xc6b2b9cd, 0x386c316c, 0x74623331, 0xc5baa896, 0xb2a7a4c1, 0x89c794a1,
	0x316bab31, 0xac688f31, 0xc8afb6cd, 0x366d3166, 0x72653c31, 0xc5b8ab94,
	0xa8b0a8bd, 0x91c58a8f, 0x317fa531, 0xa8718631, 0xb7adadcd, 0x3f753169,
	0x7a653d31, 0xc5b6a88d, 0xaaafa5bf, 0x8bc59097, 0x316dab31, 0xac699331,
	0xb5b1b3b1, 0x39703164, 0x7b6a3f31, 0xc4bda28c, 0xa9aba1a7, 0xa8c38c91,
	0x319e9031, 0x8b77be31, 0xc0b2afb6, 0x4d774281, 0x795d3131, 0xc3bea887,
	0xa7ad9faa, 0xc8ae9197, 0x31b13131, 0x62c28031, 0xc5afaccd, 0x835c31b8,
	0x706f3131, 0xc3a48a6e, 0xb7aea3b8, 0xb39c8aab, 0xa3a231a2, 0xc6653131,
	0xb8afcd81, 0x5d367bc1, 0x6431314a, 0xb88e8071, 0xa48fb8c5, 0xa68a87b9,
	0x3131c7b7, 0x6b3131a8, 0xb6c863c3, 0x49bac1b4, 0x31319575, 0x8a5b6937,
	0x92b0ae93, 0x86a6b2ad, 0xc4bba79d, 0x31c63131, 0x3fb33131, 0xc1b8b5c8,
	0x948d76b3, 0x4c513131, 0xa89c7955, 0xa99791ad, 0xa7a2798a, 0x31c5b899,
	0x31317531, 0xcb31a188, 0xbac5baad, 0x319c9662, 0x44465e31, 0xa5a08c8c,
	0x92aaa2a2, 0x8d94988e, 0x3eb1c696, 0x3131bb87, 0xa250634d, 0x9abbb8ad,
	0x3168a373, 0x51455b48, 0xa7a8947c, 0x7e90aca4, 0x8582967a, 0x94c0b29f,
	0x318fbe31, 0x5d417131, 0xb2c1b1a5, 0x31949d87, 0x4845573e, 0x9fa08b7b,
	0x83a09f9c, 0x7983867b, 0xc5afa290, 0xa03131ac, 0x8c573131, 0xb6b59a38,
	0xab9cadc9, 0x4f413165, 0x7d6f4a36, 0xbaa0aaa2, 0x818186aa, 0x93756a6c,
	0xc4c1ac9b, 0x31c2315a, 0x3f7e3731, 0xc8b7a67d, 0xb8ada5c1, 0x3c54413e,
	0x82786631, 0xb7b3b099, 0x7b847fa0, 0x887b6757, 0xc3c3b197, 0xa3936fb9,
	0x37313131, 0xbfb66931, 0xb7c2c3c8, 0x47504f84, 0x7a543131, 0xc5b69f8e,
	0x6d959dbe, 0x625d575c, 0xc2a0917d, 0x9fc1c4c3, 0x3169b645, 0x48313c31,
	0xc3c2bdb5, 0x64a8c4c5, 0x31334f4e, 0x97805c38, 0xadc3c6b9, 0x4765929c,
	0x725a514f, 0xc3bfb38a, 0x91c3c3c4, 0x3153b431, 0x555e4c31, 0xc8c2c4a5,
	0x5bbec4c5, 0x31314c3b, 0x986f5f3a, 0xc1c3c6af, 0x4a62a5a6, 0x4d3e493b,
	0xbdb39379, 0xc3c4c3c4, 0x9a31a4c2, 0x41313165, 0xbec64c31, 0xc0c5c2bf,
	0x54476bab, 0x70363137, 0xc5bb8f6f, 0x92b2c1c5, 0x363f5480, 0x94624541,
	0xc5c5b5a7, 0xb6c4c3c3, 0xb04466a2, 0x5e313131, 0xb6c77a34, 0xafc5bfc3,
	0x4f514789, 0x714c3131, 0xc5c09d7e, 0x7eb2b7bf, 0x3c445b65, 0x8f635141,
	0xc3c3aa9a, 0xacb8bebb, 0x3166a1af, 0x313131b8, 0xb67f3c89, 0xbbc7bca4,
	0x4c4d92a4, 0x53313c5f, 0x9f917571, 0xafb4c0bd, 0x5d5075a6, 0x693a3847,
	0xafa5876c, 0xb3b8bbc0, 0xa79a9aad, 0x3645658c, 0x718b3931, 0xb5bcaf34,
	0xa0a5a0c0, 0x4a6d5d9a, 0x6d714e37, 0xb19f9486, 0x9ba7a8a8, 0x615a6b77,
	0x7169384b, 0xa5ad927b, 0x9eaab6aa, 0xa094979a, 0xb83187a0, 0x8c3f3131,
	0x92b94d36, 0x99b09ac8, 0x7b7563ad, 0x73554e3c, 0x9f90875b, 0xa1ada2a5,
	0x707d7b9b, 0x4966573f, 0x8c868661, 0xaaa6b0b3, 0x8c9192a0, 0x89969689,
	0x3179c131, 0x49357244, 0xbc878489, 0x80b0b2ab, 0x4974896d, 0x6658655c,
	0x97968f7d, 0x909fa8a5, 0x4f718084, 0x523e7149, 0xa7818976, 0xa3a6a4b6,
	0x86898a9f, 0x9893958e, 0x3ba2aa55, 0x39456254, 0x91708679, 0x93a8af9a,
	0x61849176, 0x5d5b6968, 0x8c877f79, 0x989da29a, 0x73819194, 0x6a4f6b70,
	0x87726555, 0x9da79189, 0x8d959caa, 0x8e818089, 0x6583928f, 0x5b5b31c9,
	0x9a553c75, 0xa280976d, 0x8f819d95, 0x71736594, 0x786b5d70, 0x9483807b,
	0x968e9491, 0x7b7e7e90, 0x6c5d6571, 0x84746073, 0x9fa48886, 0x8e939795,
	0x817d7c82, 0x8c989486, 0x543caf5d, 0x4f4c7a61, 0x868e7c8c, 0x8d999291,
	0x7270948e, 0x72667776, 0x807a7777, 0x8e8e8a8b, 0x84848f91, 0x76727c81,
	0x79676e76, 0x88816e79, 0x93998987, 0x878b918f, 0x827d7e83, 0x68978c80,
	0x665aa06a, 0x715b7974, 0x7e867381, 0x85958e91, 0x797b918b, 0x74707a7b,
	0x7b797977, 0x8a8a8789, 0x84858e8e, 0x77797f81, 0x7a767677, 0x8478747c,
	0x8a8d7a7d, 0x898c8881, 0x7f7e8480, 0x83807d80, 0x8e8e8483, 0x7c7f7391,
	0x73786a69, 0x757c7365, 0x89897e7a, 0x868c8989, 0x7c817f80, 0x77797776,
	0x81807976, 0x86898681, 0x83868685, 0x787b7e7e, 0x79797676, 0x80807f7b,
	0x807b8680, 0x7b7f767b, 0x81857c7d, 0x84878782, 0x89858787, 0x7587918e,
	0x66626594, 0x845f6574, 0x8c818079, 0x8b8a8f8f, 0x7b7a7b8f, 0x776d707a,
	0x80797577, 0x8f878585, 0x8686888e, 0x77797b80, 0x76747375, 0x85837b7b,
	0x89888786, 0x80808486, 0x7979787c, 0x7c7b7877, 0x8583827d, 0x86868686,
	0x7d7e8183, 0x7978797b, 0x7e7b7979, 0x84848080, 0x83848486, 0x7b7c7e80,
	0x7b7a7b7b, 0x807f7d7c, 0x83838481, 0x80818384, 0x7b7c7c7e, 0x7c7b7b7b,
	0x8180807f, 0x81828282, 0x7e808080, 0x7c7c7c7e, 0x7e7e7e7c, 0x8181807e,
	0x81818181, 0x7f808081, 0x7c7d7e7e, 0x7e7e7e7d, 0x8080807f, 0x80818180,
	0x7e7f8080, 0x7d7c7c7e, 0x807e7e7d, 0x81818180, 0x7f808080, 0x7e7e7e7e,
	0x7e7e7e7d, 0x8080807e, 0x80808080, 0x7e7f8080, 0x807f7f7f, 0x807f7f7f,
	0x7f808080, 0x7e7f7e7f, 0x7e7e7f7f, 0x7e7e7e7f, 0x7f7f8080, 0x7f7f7f80,
	0x80808080, 0x807f8080, 0x7f7f8080, 0x7e7f7e80, 0x7f7f7f7f, 0x7f7f7e7f,
	0x7f7f7f7f, 0x80808080, 0x7e7e8080, 0x7e7f7e7f, 0x7e7e7e7f, 0x7f7f7f7f,
	0x0};


// irrKlang 3D sound engine example 03,
// demonstrating playing sounds directly from memory
int main(int argc, const char** argv)
{
	// start the sound engine with default parameters
	ISoundEngine* engine = createIrrKlangDevice();

	if (!engine)
		return 0; // error starting up the engine

	#ifdef __BIG_ENDIAN__
	printf("This example won't work on Power-PCs because the way we are "\
	       "storing the wave data in this example source file. Sorry.");
	return 0;
	#endif

	// To make irrKlang know about the memory we want to play, we register
	// the memory chunk as a sound source. We specify the name "testsound.wav", so
	// we can use the name later for playing back the sound. Note that you
	// could also specify a better fitting name like "ok.wav".
	// The method addSoundSource() also returns a pointer to the created sound source,
	// it can be used as parameter for play2D() later, if you don't want to
	// play sounds via string names.

	engine->addSoundSourceFromMemory(memorySoundData, memorySoundDataSize, "testsound.wav");

	// now play the sound until user presses escape

	printf("\nPlaying sound from memory.\n");
	printf("Press any key to play, ESCAPE to end program.\n");

	while(true) // endless loop until user exits
	{
		// play the sound we added to memory
		engine->play2D("testsound.wav");

		if (getch() == 27)
			break; // user pressed ESCAPE key, cancel
	}

	engine->drop(); // delete engine
	return 0;
}
