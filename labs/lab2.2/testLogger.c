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
	return 0;
}