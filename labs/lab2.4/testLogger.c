#include "logger.h"

int main(){
	infof("This is general information.\n");
	warnf("This is a warning.\n");
	errorf("Holy! This is an error.\n");
	panicf("Don't panic! Non recoverable issues with core dump.\n");

	printf("\n");
	// stdout logging
	initLogger("stdout");   
	infof("This is general information.\n");
	warnf("This is a warning.\n");
	errorf("Holy! This is an error.\n");
	panicf("Don't panic! Non recoverable issues with core dump.\n");

	printf("\n");
	printf("Check at /var/log/syslog \n");
	
	// syslog logging
	initLogger("syslog");   
	infof("[info]\n");
	warnf("[warn] %s \n", "warn");
	errorf("[error] %s %s \n", "error", "test");
   	panicf("[panic]\n");

	return 0;
}

