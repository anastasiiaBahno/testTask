#include <iostream>
#include <cmath>

#include "log.h"
#include "JpegUtils.hpp"


JpegSource::JpegSource(const std::string& path) 
    : mPath(path) {

    mCinfo.err = jpeg_std_error(&mJerr);	
    jpeg_create_decompress(&mCinfo);
}

JpegSource::~JpegSource() {
    jpeg_destroy_decompress(&mCinfo);
    if (mInfile != nullptr) 
        fclose(mInfile);
}

bool JpegSource::init() {
    if ((mInfile = fopen(mPath.c_str(), "rb")) == NULL) {
        LOG_ERROR << "Could not open file " << mPath;
        return false;
    }

    jpeg_stdio_src(&mCinfo, mInfile);
    if (JPEG_SUSPENDED == jpeg_read_header(&mCinfo, TRUE)) {
        LOG_ERROR << "Could not read header";
        return false;
    }

    mCinfo.out_color_space = JCS_YCbCr;


    return true;
}

void JpegSource::process() {
    jpeg_start_decompress(&mCinfo);
    LOG_INFO << "Color space: " << mCinfo.jpeg_color_space << ", output_components: "  << mCinfo.output_components 
        << " out_color_components: " << mCinfo.out_color_components
        << " output_gamm: " << mCinfo.output_gamma << ", rec_outbuf_height: " << mCinfo.rec_outbuf_height;
    int rowSize = mCinfo.output_width * mCinfo.output_components;
    std::vector<unsigned char> row(rowSize, 0);
    while (mCinfo.output_scanline < mCinfo.output_height) {
		unsigned char *buffer_array[1];
        buffer_array[0] = &row[0];
		jpeg_read_scanlines(&mCinfo, buffer_array, 1);
        onRowRead(row);
	}

    jpeg_finish_decompress(&mCinfo);
}

JpegBlendedSink::~JpegBlendedSink() {
    jpeg_destroy_compress(&mCinfo);
    if (mOutfile != nullptr) 
        fclose(mOutfile);
}

JpegBlendedSink::JpegBlendedSink(const std::string& path) 
    : mPath(path) {

    mCinfo.err = jpeg_std_error(&mJerr);
    jpeg_create_compress(&mCinfo);
}

bool JpegBlendedSink::init(int width, int height, int quality, int componentsPerPixel) {
    if ((mOutfile = fopen(mPath.c_str(), "wb")) == NULL) {
        LOG_ERROR << "Could not open file " << mOutfile;
        return false;
    }
    jpeg_stdio_dest(&mCinfo, mOutfile);

    mCinfo.image_width = width; 	
    mCinfo.image_height = height;
    mCinfo.input_components = 3;		
    mCinfo.in_color_space = JCS_YCbCr;
    jpeg_set_defaults(&mCinfo);
    jpeg_set_quality(&mCinfo, 80, TRUE);
    jpeg_start_compress(&mCinfo, TRUE);
    return true;
}

void JpegBlendedSink::processRow(std::vector<unsigned char>& inRow) {
    JSAMPROW row_pointer[1];

    if (!mPrevRow.empty()) {
        for (int i = 0 ; i < inRow.size(); ++i) {
            inRow[i] = 0.5 * (inRow[i] + mPrevRow[i]);
        }
    } 
    
    row_pointer[0] = &inRow[0];
    (void)jpeg_write_scanlines(&mCinfo, row_pointer, 1);
    
    mPrevRow = inRow;
}

void JpegBlendedSink::flush() {
    jpeg_finish_compress(&mCinfo);
}