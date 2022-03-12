#include <stdio.h>
#include <direct.h>
#include <string.h>

void main(){
	char dir[FILENAME_MAX];
	_getcwd(dir, sizeof(dir));
	FILE* f = fopen("ins.reg","w");
	
	char def[] = "Windows Registry Editor Version 5.00\n[HKEY_CLASSES_ROOT\\*\\shell\\test_ex]\n\"MUIVerb\"=\"test_ex\"\n\"Position\"=\"Top\"\n\n[HKEY_CLASSES_ROOT\\*\\shell\\test_ex\\command]\n\"(Default)\"=\"";
	
	fprintf(f,"%s",def);


	for (int i=0;i<strlen(dir)-7;++i){
		fprintf(f,"%c",dir[i]);
	       if (dir[i] == '\\'){
	       	fprintf(f,"\\");
	       }	       
	}
	char def_end[] = "main_code\\\\main.exe \\\"%1\\\"\"";
	fprintf(f,"%s",def_end);

	fclose(f);

	system("Regedit ins.reg");
}
