#include"r232lc.h"
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/termios.h>

struct protocol_header_t{
	uint8_t command;	/*	*/
	uint8_t data;		/*	*/
};

#define R232LCP_SET_STATEL      0x0	/*	Set state in low byte.	*/
#define R232LCP_SET_STATEH      0x1	/*	Set state in high byte.	*/
#define R232LCP_SET_LEDD        0x2	/*	Set current LED data.	*/
#define R232LCP_SET_ANIM        0x3	/*	Set internal animation sequence.	*/
#define R232LCP_SET_PWM         0x4	/*	Set PWM for the LED.	*/
#define R232LCP_SET_BAUD        0x5	/*	Set Baud rate.	*/
#define R232LCP_GET_BAUD        0xD	/*	Get Baud rate.	*/
#define R232LCP_GET_STATE       0xE	/*	Get current state.	*/
#define R232LCP_GET_VERSION     0xF	/*	Get version in string format.	*/


static inline int rs232lc_write(const RS232LC* __restrict__ state, uint32_t command,
		const uint8_t* __restrict__ buf, size_t len) {

	int i;
	int e = 0;
	struct protocol_header_t prot;

	/*	Iterate through each byte.	*/
	for(i = 0; i < len; i++){
		/*	command and data byte.	*/
		prot.command = command;
		prot.data = buf[i];

		/*	Send two byte at a time .*/
		e += write(state->fd, &prot, sizeof(struct protocol_header_t));
	}

	return e;
}

static inline int rs232lc_read(const RS232LC* __restrict__ state,
		uint8_t* __restrict__ buf, size_t len) {
	return read(state->fd, buf, len);
}

int rs232lc_init(RS232LC* state, int fd){

	struct termios settings;

	/*	Check valid fd.	*/
	if(fd < 0)
		return 0;

	/*	Get serial attribute settings.	*/
	if(tcgetattr(fd, &settings) < 0){
		fprintf(stderr, "tcgetattr failed, %s.\n", strerror(errno));
		return 0;
	}

	/*	*/
	settings.c_cflag &= ~PARENB;		/* no parity */
	settings.c_cflag &= ~CSTOPB;		/* 1 stop bit */
	settings.c_cflag &= ~CSIZE;			/*	*/
	settings.c_cflag |= CS8 | CLOCAL;	/* 8 bits */
	settings.c_lflag = ICANON;			/* canonical mode */
	settings.c_oflag &= ~OPOST;			/* raw output */

	/*	apply the serial attribute settings.	*/
	if(tcsetattr(fd, TCSANOW, &settings)){
		fprintf(stderr, "tcsetattr failed, %s.\n", strerror(errno));
		return 0;
	}

	/*	*/
	tcflush(fd, TCOFLUSH);

	/*	Initial state.	*/
	state->fd = fd;
	state->state = 0;
	state->anim = 0;
	rs232lc_set_baud(state, BAUD9600);
	rs232lc_set_pwm(state, 192);
	
	return 1;
}

int rs232lc_close(RS232LC* state){

	/*	*/
	if(tcflush(state->fd)){
		fprintf(stderr, "tcflush failed, %s.\n", strerror(errno));
		return 0;

	}

	/**/
	close(state->fd);

	/*	Reset serial settings.	*/

	return 1;
}

void rs232lc_set_pwm(RS232LC* state, uint8_t pwm){
	rs232lc_write(state, R232LCP_SET_PWM, (const uint8_t*)&pwm, 1);
}
uint8_t rs232lc_get_pwm(RS232LC* state){

	uint8_t pwm;

	rs232lc_read(state, &pwm, 1);

	return 1;
}

int rs232lc_set_baud(RS232LC* state, uint8_t baud){

	struct termios settings;

	/*	Get terminal settings.	*/
	if(tcgetattr(state->fd, &settings) != 0){
		fprintf(stderr, "tcgetattr failed, %s.\n", strerror(errno));
		return 0;
	}

	/*	*/
	rs232lc_write(state, R232LCP_SET_BAUD, (const uint8_t*)&baud, 1);

	/*	Sync .	*/


	/*	Set output baud rate.	*/
	if(cfsetospeed(&settings, (speed_t)baudrates[baud]) != 0){
		fprintf(stderr, "cfsetospeed failed, %s.\n", strerror(errno));
	}

	/*	Set input baud rate.	*/
	if(cfsetispeed(&settings, (speed_t)baudrates[baud]) != 0){
		fprintf(stderr, "cfsetispeed failed, %s.\n", strerror(errno));
	}

	/*	*/
	tcflush(state->fd, NOFLSH);


	return 1;
}
uint8_t rs232lc_get_baud(RS232LC* state){

	uint8_t baud;

	rs232lc_read(state, &baud, 1);

	return baud;
}

int rs232lc_set_rgb(RS232LC* state, uint32_t rgb){
	return rs232lc_write(state, R232LCP_SET_LEDD, (const uint8_t*)&rgb, 3);
}

void rs232lc_set_anim(RS232LC* state, uint32_t anim){
	rs232lc_write(state, R232LCP_SET_ANIM, &anim, 1);
}
uint32_t rs232lc_get_anim(const RS232LC* state){
	uint32_t anim;

	rs232lc_read(state, &anim, 1);

	return anim;
}

void r232lc_set_state(RS232LC* state, uint32_t lc_state){
	uint8_t lh = (lc_state & 0xff);
	uint8_t hh = (lc_state & 0xff);

	rs232lc_write(state, R232LCP_SET_STATEL, &lh, 1);
	rs232lc_write(state, R232LCP_SET_STATEH, &hh, 1);
}
uint32_t r232lc_get_state(const RS232LC* state){
	uint32_t lc_state;

	rs232lc_write(state, R232LCP_GET_STATE, 0, 0);
	rs232lc_read(state, &lc_state, 2);

	return state;
}

void rs232lc_get_version(const RS232LC* state, char* pversion){
	rs232lc_read(state, (uint8_t*)pversion, 10);
}

const char* rs232lc_version(void){
	return "";
}
