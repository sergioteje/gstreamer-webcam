# gstreamer-webcam
Partial implementation of a solution for streaming video and audio from a webcam to a webpage using GStreamer

There are two main parts in this repository:

1 - GStreamer implementation to obtain the video of a web camera.

An application has been written in C++ in order to create a pipeline that shows a pop up window with the image sent by a web camera.

Although it seems that the most widely used GStreamer element for this purpose is "v4l2src", it is disabled since version 1.14 of GStreamer due to major bugs (https://gstreamer.freedesktop.org/documentation/video4linux2/v4l2src.html?gi-language=c). Because of this, the element "ksvideosrc" has been used instead.

The code has been originally implemented in Microsoft Visual Studio. The dependencies with the GStreamer libraries has been therefore configured there. The whole Visual Studio project is included in this repository, in the folder called "webcamStreaming". The source files can be found under /webcamStreaming. It is two files called StreamingData.cpp and main.cpp. The compiled executable file is also included at the path "/x64/Debug/webcamStreaming.exe".

In case the code wants to be compiled manually, a compiler like G++ can be used. The libraries glib-2.0 and gstreamer-1.0 must be added to the "included" files.

For example, in my case, I have added the following configuration to the additional include directories of Visual Studio:

C:\gstreamer\1.0\msvc_x86_64\lib\glib-2.0\include;C:\gstreamer\1.0\msvc_x86_64\include\gstreamer-1.0;C:\gstreamer\1.0\msvc_x86_64\include\glib-2.0\;%(AdditionalIncludeDirectories)

2 - NodeJS server for the communication between WebRTC and GStreamer.

In order for the web page to communicate with GStreamer, a server is needed to facilitate the retrieval of the streaming information. In this case, I propose the use of a NodeJS/Express server, whose main structure is included in the folder nodeJsServer. The main endpoints that would be used to get/send information to the GStreamer application are included. Unfortunately, its implementation are not coded due to a lack of time.


