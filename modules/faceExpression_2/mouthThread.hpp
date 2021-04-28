#ifndef MOUTH_THREAD_HPP
#define MOUTH_THREAD_HPP

#include <mutex>
#include <string>
#include <iostream>

#include <opencv2/core/version.hpp>
#include <opencv2/core/mat.hpp>

#include <yarp/sig/Image.h>
#include <yarp/os/Network.h>
#include <yarp/os/RFModule.h>
#include <yarp/os/LogStream.h>
#include <yarp/os/PeriodicThread.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/os/ResourceFinder.h>
#include <yarp/dev/audioRecorderStatus.h>
#include <yarp/dev/audioPlayerStatus.h>

#define VOCAB_AUDIO_START       yarp::os::createVocab('a','s','t','a')
#define VOCAB_AUDIO_STOP        yarp::os::createVocab('a','s','t','o')
#define VOCAB_TALK_START        yarp::os::createVocab('t','s','t','a')
#define VOCAB_TALK_STOP         yarp::os::createVocab('t','s','t','o')
#define VOCAB_BLINK             yarp::os::createVocab('b','l','i','n')
#define VOCAB_RESET             yarp::os::createVocab('r','s','t')
#define VOCAB_BLACK_RESET       yarp::os::createVocab('b','l','c','k')

class MouthThread : public yarp::os::PeriodicThread
{
public:
    MouthThread(yarp::os::ResourceFinder& _rf, double _period, cv::Mat& _image, std::mutex& _mutex);

    yarp::os::ResourceFinder& m_rf;
    yarp::os::BufferedPort<yarp::dev::audioPlayerStatus > m_audioPlayPort;
    std::mutex& m_mutex;
    std::string m_imagePath;

    cv::Mat&                m_face;
    cv::Mat                 defaultPlainMouth;
    cv::Mat                 blackMouth;

    size_t                  mouth_w=16;
    size_t                  mouth_h=3;

    // Offset values for placing stuff and size
    int barWidth;

    bool threadInit()  override;
    void threadRelease()  override;
    void afterStart(bool s)  override;
    void run() override;

    void activateTalk (bool activate);
    void updateTalk();

    bool m_doTalk;

private:

    bool m_audioIsPlaying=false;
};

#endif
