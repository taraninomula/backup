
struct file_ops {
	char d_name[16];
	int (*open) (int x);
	int (*read) (int y);
};

