#pragma once

#include <sys/un.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/mman.h>
#include <inttypes.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <Dobby/dobby.h>

typedef unsigned long ulong;

#if defined(__arm__)
#include <SubstrateHook.h>
#elif defined(__aarch64__)
#include <And64InlineHook.hpp>
#endif

#define LOG_TAG "Aneko"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

void hook(void *address, void *new_fn, void **old_fn);
#define HOOK(address, new_fn, old_fn) hook(reinterpret_cast<void*>((address)), reinterpret_cast<void*>(new_fn), reinterpret_cast<void**>(old_fn));

inline pid_t pid = 0;

inline void hook(void *address, void *new_fn, void **old_fn) {
#if defined(__arm__)
    MSHookFunction(address, new_fn, old_fn);
#elif defined(__aarch64__)
    A64HookFunction(address, new_fn, old_fn);
#endif
}

inline uintptr_t get_module_base(int pid, const char *module_name)
{
	FILE *fp;
	uintptr_t addr = 0;
	char *pch;
	char filename[32];
	char line[1024];
	snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);
	fp = fopen(filename, "r");
	if (fp != NULL)
	{
		while (fgets(line, sizeof(line), fp))
		{
			if (strstr(line, module_name))
			{
				pch = strtok(line, "-");
				addr = (uintptr_t)strtoul(pch, NULL, 16);
				break;
			}
		}
		fclose(fp);
	}
	return addr;
}

/*
#if defined(__arm__)
int process_vm_readv_syscall = 376;
int process_vm_writev_syscall = 377;
#elif defined(__aarch64__)
int process_vm_readv_syscall = 270;
int process_vm_writev_syscall = 271;
#elif defined(__i386__)
int process_vm_readv_syscall = 347;
int process_vm_writev_syscall = 348;
#else
int process_vm_readv_syscall = 310;
int process_vm_writev_syscall = 311;
#endif


inline ssize_t process_v(pid_t __pid, struct iovec* __local_iov, ulong __local_iov_count, struct iovec* __remote_iov, ulong __remote_iov_count, ulong __flags) {
	return syscall(process_vm_readv_syscall, __pid, __local_iov, __local_iov_count, __remote_iov, __remote_iov_count, __flags);
}

inline ssize_t process_vm_writev(pid_t __pid, struct iovec* __local_iov, ulong __local_iov_count, struct iovec* __remote_iov, ulong __remote_iov_count, ulong __flags) {
	return syscall(process_vm_writev_syscall, __pid, __local_iov, __local_iov_count, __remote_iov, __remote_iov_count, __flags);
}

inline int pvm(uintptr_t address, void* buffer,int size) {
	struct iovec local[1];
	struct iovec remote[1];

	local[0].iov_base = buffer;
	local[0].iov_len = size;
	remote[0].iov_base = (void*)address;
	remote[0].iov_len = size;

    ssize_t bytes = process_v(pid, local, 1, remote, 1, 0);
	return bytes == size;
}

inline bool pvms(void* address, void* buffer, size_t size, bool iswrite) {
    struct iovec local[1];
    struct iovec remote[1];
    local[0].iov_base = buffer;
    local[0].iov_len = size;
    remote[0].iov_base = address;
    remote[0].iov_len = size;
    if (pid < 0) {
        return false;
    }
    ssize_t bytes = syscall((iswrite ? process_vm_writev_syscall : process_vm_readv_syscall), pid, local, 1, remote, 1, 0);
    return bytes == size;
}

inline bool vm_readv(void* address, void* buffer, size_t size) {
    return pvms(address, buffer, size, false);
}

inline bool vm_writev(void* address, void* buffer, size_t size) {
    return pvms(address, buffer, size, true);
}*/
