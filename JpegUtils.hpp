#pragma once

#include <string>
#include <vector>
#include <boost/signals2.hpp>

#include <jpeglib.h>

class JpegSource {
public:
    boost::signals2::signal<void (std::vector<unsigned char>&)>  onRowRead;

    JpegSource(const std::string& path);
    ~JpegSource();
    bool init();
    int height() { return mCinfo.image_height; }
    int width() { return mCinfo.image_width; }
    int numComponents() { return mCinfo.output_components; }

    void process();

private:
    std::string mPath;

    struct jpeg_decompress_struct mCinfo;
	struct jpeg_error_mgr mJerr;
    FILE * mInfile = nullptr;
};

class JpegSink {
public:
    JpegSink(const std::string& path);
    ~JpegSink();
    bool init(int width, int height, int quality, int componentsPerPixel);
    void processRow(std::vector<unsigned char>&);
    void flush();

private:
    std::string mPath;
    struct jpeg_compress_struct mCinfo;
    struct jpeg_error_mgr mJerr;
    FILE * mOutfile = nullptr;	

    std::vector<unsigned char> mPrevRow;
};
