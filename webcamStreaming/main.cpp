#include <gst/gst.h>
#include "StreamingData.cpp"

/**
    Implementation of a streaming pipeline that receives the video signal from a camera and sends it to a default sink to be viewed on a popup window
    @author Sergio Tejeda Pastor
    @version 1.0
*/
int main(int argc, char* argv[]) {

    // The basic data is stored in a 
    StreamingData data;
    GstBus* bus;
    GstMessage* msg;
    GstStateChangeReturn ret;

    /* Initialize GStreamer */
    gst_init(&argc, &argv);

    /* Create the necessary elements of the pipeline*/
    data.source = gst_element_factory_make("ksvideosrc", "source");
    data.videoConvert = gst_element_factory_make("videoconvert", "converter");
    data.sink = gst_element_factory_make("autovideosink", "sink");

    /* Modify the source's properties */
    g_object_set(data.source, "device-index", 0, NULL);
    g_object_set(data.source, "do-stats", TRUE, NULL);

    /* Create the empty pipeline */
    data.pipeline = gst_pipeline_new("webcam-pipeline");

    if (!data.pipeline || !data.source || !data.videoConvert || !data.sink) {
        g_printerr("The creation of the elements was unsuccsessful.\n");
        return -1;
    }

    /* Build the pipeline */
    gst_bin_add_many(GST_BIN(data.pipeline), data.source, data.videoConvert, data.sink, NULL);
    if (gst_element_link(data.source, data.videoConvert) != TRUE || gst_element_link(data.videoConvert, data.sink) != TRUE) {
        g_printerr("The elements of the pipeline could not be linked.\n");
        gst_object_unref(data.pipeline);
        return -1;
    }

    // The pipeline is set to the state Playing
    ret = gst_element_set_state(data.pipeline, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        g_printerr("The pipeline could not be set to the Playing state.\n");
        gst_object_unref(data.pipeline);
        return -1;
    }

    // The execution will go on until the streaming is stopped or an error appears
    bus = gst_element_get_bus(data.pipeline);
    msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, (GstMessageType)(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));

    /* Parsing of the received message */
    if (msg != NULL) {
        GError* err;
        gchar* debug_info;

        switch (GST_MESSAGE_TYPE(msg)) {
        case GST_MESSAGE_ERROR:
            gst_message_parse_error(msg, &err, &debug_info);
            g_printerr("Error received from element %s: %s\n",
                GST_OBJECT_NAME(msg->src), err->message);
            g_printerr("Debugging information: %s\n",
                debug_info ? debug_info : "none");
            g_clear_error(&err);
            g_free(debug_info);
            break;
        case GST_MESSAGE_EOS:
            g_print("The stream has ended.\n");
            break;
        default:
            g_printerr("Unexpected message received. Nothing will be done\n");
            break;
        }
        gst_message_unref(msg);
    }

    /* Set pipeline state to NULL and free allocated resources */
    gst_object_unref(bus);
    gst_element_set_state(data.pipeline, GST_STATE_NULL);
    gst_object_unref(data.pipeline);
    return 0;
}