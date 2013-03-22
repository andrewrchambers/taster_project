#ifndef ADVCL_CLL_H_INCLUDED
#define ADVCL_CLL_H_INCLUDED

#define __CL_ENABLE_EXCEPTIONS

#include <vector>
#include <string>
#include <CL/cl.hpp>

#include "particle.hpp"

class Scorer {
  public:
    //default constructor initializes OpenCL context 
    Scorer(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
    //default destructor releases OpenCL objects and frees device memory
    ~Scorer();
    //load an OpenCL program from a given filename
    void loadProgram(const std::string&);
    // Setup the data for the kernel (I.e. the renderbuffer
    // and the depth texture)
    void loadData(GLuint, GLuint);
    // This does the real work - i.e. runs the kernel and accumulates
    // scores for all renderings
    std::vector<double> calculateScores(std::vector<Particle>&);

    // This just waits for everything to finish...
    void finish() { queue.finish(); };
  private:

    void loadProgramFromString(const std::string&);
    double getCollisionPenalty(Particle&);

    std::vector<cl::Memory> clObjects;  // 0: renderbuffer, 1: depth texture
    cl::Buffer differenceBuffer; 
    cl::Buffer unionBuffer; 
    cl::Buffer intersectionBuffer;
    unsigned int dm, dM;
    unsigned int numScores;    //the number of particles
    unsigned int imageWidth;
    unsigned int imageHeight;

    size_t arraySize;
    unsigned int deviceUsed;
    std::vector<cl::Device> devices;
    cl::Context context;
    cl::CommandQueue queue;
    cl::Program program;
    cl::Kernel kernel;
    //debugging variables
    cl_int err;
    ///cl_event event;
    cl::Event event;
};

#endif
