#include <gst/gst.h>

/**
    Class that includes the necessary elements of the streaming application
    @author Sergio Tejeda Pastor
    @version 1.0
*/
class StreamingData {

    public:

        GstElement* pipeline;

        GstElement* source;

        GstElement* videoConvert;

        GstElement* sink;

};
