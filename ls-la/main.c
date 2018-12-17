#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

int one_scan(struct dirent * dirr)
{
	char * path_buff;
	path_buff = calloc(sizeof(char)*(strlen(dirr->d_name)) + 2, sizeof(char));
	path_buff[0] = '.';
	path_buff[1] = '/';
	strcpy(&(path_buff[2]), dirr->d_name);

	struct stat Stat;
	memset(&Stat, 0, sizeof(struct stat));
	stat(path_buff, &Stat);
	printf((Stat.st_mode & S_IFDIR)?"d":"-");
	printf((Stat.st_mode & S_IRUSR)?"r":"-");
	printf((Stat.st_mode & S_IWUSR)?"w":"-");
	printf((Stat.st_mode & S_IXUSR)?"x":"-");
	printf((Stat.st_mode & S_IRGRP)?"r":"-");
	printf((Stat.st_mode & S_IWGRP)?"w":"-");
	printf((Stat.st_mode & S_IXGRP)?"x":"-");
	printf((Stat.st_mode & S_IROTH)?"r":"-");
	printf((Stat.st_mode & S_IWOTH)?"w":"-");
	printf((Stat.st_mode & S_IXOTH)?"x":"-");
	printf(" %1d", Stat.st_nlink);
	struct passwd * pwd;
	pwd = getpwuid(Stat.st_uid);
	printf(" %s", pwd->pw_name);
	struct group * grp;
	grp = getgrgid(Stat.st_gid);
	printf(" %s", grp->gr_name);
	printf(" %5d ", (int)Stat.st_size);
	struct tm * time_ptr;
	time_t It = Stat.st_ctime;
	time_ptr = localtime(&It);
	printf(" %02d.%02d", time_ptr->tm_mday, time_ptr->tm_mon+1);
	printf(" %02d:%02d ", time_ptr->tm_hour, time_ptr->tm_min);
	printf("%s", dirr->d_name);
	printf("\n");
	
	return 0;
}

int main()
{
	int n;
	struct dirent ** entry;
	if(-1 == (n = scandir("./", &entry, NULL, alphasort)))
		return 1;
	else
	{
	}
	printf("%d files in directory\n", n);
	int dir_size = n-1;
	while(n!=0){
		one_scan(entry[dir_size - n]);
	}
	return 0;
}
