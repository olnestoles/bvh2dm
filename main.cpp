#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include "BVHReader.h"
#include "Motion.h"
#include "KinTree.h"

#define FRAME_RATE 25

template<class T>
T base_name(T const & path, T const & delims = "/\\")
{
  return path.substr(path.find_last_of(delims) + 1);
}
template<class T>
T remove_extension(T const & filename)
{
  typename T::size_type const p(filename.find_last_of('.'));
  return p > 0 && p != T::npos ? filename.substr(0, p) : filename;
}

int converter(const char *bvh_file, const char *out_dir) {
    
    std::stringstream ss_motion;
    std::stringstream ss_character;
    std::string path(bvh_file);
    std::string file_without_extension = remove_extension(base_name(path));
    ss_motion << out_dir << "/" << file_without_extension <<".motion";
    ss_character << out_dir << "/" << file_without_extension <<".char";
    
    cBVHReader *bvh = new cBVHReader();
    bvh->parseBVH(bvh_file);
    cMotion out_motion;
    Eigen::MatrixXd out_joint_mat;
    bvh->BuildMotion(FRAME_RATE, out_motion);
    bvh->BuildJointMat(out_joint_mat);
    out_motion.Output(ss_motion.str().c_str());
    
    std::string json = cKinTree::BuildJointMatJson(out_joint_mat, bvh);
    std::stringstream ss;
    ss << "{\n \"Skeleton\": \n" << json << "\n}";
    
    std::string json_full = ss.str();
    
    std::ofstream myfile (ss_character.str());
    if(myfile.is_open()) 
    {
        myfile << json_full;
        myfile.close();
        return 0;
    } else
        return -1;
}

void Usage(char **argv) {
    
    std::cout << "Err: wrong arguments count" << std::endl;
    std::cout << "Usage:" << argv[0] << " -b BVH_FILE.bvh -o OUTPUT_DIR" << std::endl;
    exit(-1);
}

int main(int argc, char** argv) {

    int opt;
    const char* bvh_file = 0;
    const char* output = 0;

    if (argc != 5)
        Usage(argv);

    while ((opt = getopt(argc, argv, "bo")) != -1) {
        switch (opt) {
            case 'b':
                bvh_file = argv[2];
                std::cout << "Bvh file:" << bvh_file << std::endl;
                break;
            case 'o':
                output = argv[4];
                std::cout << "Output dir:" << output << std::endl;
                break;
            case '?':
                std::cerr << "Unknown option: '" << char(optopt) << "'!" << std::endl;
                break;
        }
    }

    return converter(bvh_file, output);
}

