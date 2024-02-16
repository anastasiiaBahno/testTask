#include <iostream>
#include <string>

#include <boost/program_options.hpp>

#include "JpegUtils.hpp"
#include "log.h"


int main(int argc, char* argv[]) {

    std::string ofile;
    std::string ifile;
 
    boost::program_options::options_description desc("Options");
        desc.add_options()
        ("help", "print usage message")
        ("output", boost::program_options::value(&ofile), "pathname for output file")
        ("input", boost::program_options::value(&ifile), "pathname for input")
        ;

    boost::program_options::variables_map vm;
    boost::program_options::store(parse_command_line(argc, argv, desc), vm);

    if (vm.count("help")) {  
        LOG_INFO << desc;
        return 0;
    }

    if (vm.count("input")) {
        ifile = vm["input"].as<std::string>();
    } else {
        LOG_ERROR << "Input file is not provided ";
        LOG_INFO << desc;
        return 0;
    }

    if (vm.count("output")) {
        ofile = vm["output"].as<std::string>();      
    }  else {
        LOG_ERROR << "Output file is not provided ";
        LOG_INFO << desc;
        return 0;
    }         

    JpegSource src(ifile);
    if (!src.init()) {
        LOG_ERROR << "Could not initialize jpeg source";
        return 0;
    }
    
    JpegBlendedSink sink(ofile);

    const int quality = 75;
    if (!sink.init(src.width(), src.height(), quality, src.numComponents())) {
        LOG_ERROR << "Could not initialize sink ";
        return 0;
    }

    src.onRowRead.connect(boost::bind(&JpegBlendedSink::processRow, &sink, _1));

    src.process();
    sink.flush();
    return 0;
}



// Mat ycbcr;
// cvtColor(bgr,ycbcr,CV_BGR2YCBCR);

// Mat chan[3];
// split(ycbcr,chan);

// Mat y  = chan[0];
// Mat cb = chan[1];
// Mat cr = chan[2];