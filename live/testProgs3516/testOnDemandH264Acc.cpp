#include "liveMedia.hh"

#include "BasicUsageEnvironment.hh"
#include "announceURL.hh"
#include "GroupsockHelper.hh"

UsageEnvironment* env;

// To make the second and subsequent client for each stream reuse the same
// input stream as the first client (rather than playing the file from the
// start for each client), change the following "False" to "True":
Boolean reuseFirstSource = False;

static void announceStream(RTSPServer* rtspServer, ServerMediaSession* sms,
			   char const* streamName, char const* inputFileName); // forward


int main()
{ 
  // Begin by setting up our usage environment:
  TaskScheduler* scheduler = BasicTaskScheduler::createNew();
  env = BasicUsageEnvironment::createNew(*scheduler);

  UserAuthenticationDatabase* authDB = NULL;
#ifdef ACCESS_CONTROL
  // To implement client access control to the RTSP server, do the following:
  authDB = new UserAuthenticationDatabase;
  authDB->addUserRecord("username1", "password1"); // replace these with real strings
  // Repeat the above with each <username>, <password> that you wish to allow
  // access to the server.
#endif

  // Create the RTSP server.  Try first with the default port number (554),
  // and then with the alternative port number (8554):
  RTSPServer* rtspServer;
  portNumBits rtspServerPortNum = 554;
  rtspServer = RTSPServer::createNew(*env, rtspServerPortNum, authDB);
  if (rtspServer == NULL) {
    rtspServerPortNum = 8554;
    rtspServer = RTSPServer::createNew(*env, rtspServerPortNum, authDB);
  }
  if (rtspServer == NULL) {
    *env << "Failed to create RTSP server: " << env->getResultMsg() << "\n";
    exit(1);
  }

  char const* descriptionString
    = "Session streamed by \"testOnDemandRTSPServer\"";


	char const* streamName = "h264ESVideoTest";
    //char const* inputFileName = "test.264";
	char const* inputFileName = "test.264";
    char const* inputFileName1 = "test.aac";
    ServerMediaSession* sms
      = ServerMediaSession::createNew(*env, streamName, streamName,
                      descriptionString);
    sms->addSubsession(H264VideoFileServerMediaSubsession
               ::createNew(*env, inputFileName, reuseFirstSource));
    sms->addSubsession(ADTSAudioFileServerMediaSubsession
        ::createNew(*env, inputFileName1, reuseFirstSource));
    rtspServer->addServerMediaSession(sms);

    announceStream(rtspServer, sms, streamName, inputFileName);


/* 循环处理事件 */
    env->taskScheduler().doEventLoop();

    return 0;

}


static void announceStream(RTSPServer* rtspServer, ServerMediaSession* sms,
			   char const* streamName, char const* inputFileName) {
  UsageEnvironment& env = rtspServer->envir();

  env << "\n\"" << streamName << "\" stream, from the file \""
      << inputFileName << "\"\n";
  announceURL(rtspServer, sms);
}