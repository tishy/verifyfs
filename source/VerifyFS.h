/*
 * Copyright (c) 2015, Cognitive-i Ltd (verifyfs@cognitive-i.com)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this
 *    list of conditions and the following disclaimer in the documentation and/or
 *    other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef VERIFYFS_H
#define VERIFYFS_H

#include "IFuseFSProvider.h"
#include <dirent.h>

#include <string>
#include <map>
#include <vector>

class VerifyFS : public IFuseFSProvider
{
public:
    VerifyFS(const std::string& untrustedPath, const std::map<std::string, std::string> fileHashes);

    // IFuseFSProvider interface
    virtual int fuseStat(const char* path, struct stat* stbuf);
    virtual int fuseOpendir(const char* path, struct fuse_file_info* fi);
    virtual int fuseReaddir(const char* path, void* buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info* fi);
    virtual int fuseReleasedir(const char* path, struct fuse_file_info* fi);
    virtual int fuseOpen(const char* path, struct fuse_file_info* fi);
    virtual int fuseRead(const char* path, char* buf, size_t size, off_t offset, struct fuse_file_info* fi);
    virtual int fuseRelease(const char* path, struct fuse_file_info* fi);

private:
    int openAndVerify(const std::string& path, const std::string& expectedDigest);

private:
    const std::string mUntrustedPath;
    const std::map<std::string, std::string> mTrustedFileHashes;
    std::map<std::string, std::vector<uint8_t>> mTrustedFiles;

    std::map<int, DIR*> fdDir;

};

#endif // VERIFYFS_H