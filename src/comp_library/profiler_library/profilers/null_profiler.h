//-*-C++-*-

#ifndef DCA_NOPROFILING_H
#define DCA_NOPROFILING_H

namespace PROFILER 
{
  /*! 
   *  \defgroup NO-PROFILING
   *  \ingroup  PROFILING
   */
 
  /*! 
   * \ingroup NO-PROFILING
   *
   */
  class no_profiling_mode 
  {
  public:
    
    no_profiling_mode(const char* /*functionName_*/,
                      const char* /*fileName_*/,
                      int         /*line*/,
                      bool        /*bogusArgument*/=true)
    {}
    
    no_profiling_mode(std::ostringstream& /*functionNameStrm*/,
                      const char*         /*fileName_*/,
                      int                 /*line*/,
                      bool                /*bogusArgument*/=true)
    {}

    ~no_profiling_mode(){}

    static void start_pthreading(int /*id*/)
    {}

    static void stop_pthreading(int /*id*/)
    {}

    static void start()
    {}

    static void stop(std::string /*fileName*/) 
    {}

    template<typename ParallelProcessingType>    
    static void stop(const ParallelProcessingType& /*parallelProcessing*/,
                     std::string                   /*fileName*/) 
    {}

 };

}

#endif



