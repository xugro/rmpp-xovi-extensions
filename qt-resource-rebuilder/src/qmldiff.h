#pragma once
extern int qmldiff_build_change_files(const char *rootDir);
extern char *qmldiff_process_file(const char *fileName, char *contents);
extern char qmldiff_is_modified(const char *fileName);
extern void qmldiff_start_saving_thread();
