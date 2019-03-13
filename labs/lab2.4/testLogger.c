int initLogger (char *logType);
int infof(const char *format, ...);
int warnf(const char *format, ...);
int errorf(const char *format, ...);
int panicf(const char *format, ...);
void textcolor(int attr, int fg);

int main(){
	infof("This is general information.\n");
	warnf("This is a warning.\n");
	errorf("Holy! This is an error.\n");
	panicf("Don't panic! Non recoverable issues with core dump.\n");

	printf("\n");

	initLogger("stdout");   
	infof("This is general information.\n");
	warnf("This is a warning.\n");
	errorf("Holy! This is an error.\n");
	panicf("Don't panic! Non recoverable issues with core dump.\n");

	printf("\n");
	printf("Check at /var/log/syslog \n");
	initLogger("syslog");   
	infof("[info]\n");
	warnf("[warn] %s \n", "warn");
	errorf("[error] %s %s \n", "error", "test");
   	panicf("[panic]\n");

	return 0;
}

