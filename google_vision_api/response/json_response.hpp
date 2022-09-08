#pragma once
/**
  * json_response.hpp
 * 2020-07-01 K.OHWADA
 */


#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>


/**
 * struct vertice
 */
struct vertice
{
    int x;
    int y;
};


/**
 * struct boundingPoly
 */
struct boundingPoly
{
    std::vector<struct vertice> vertices;
};


/**
 * struct fdBoundingPoly
 */
struct fdBoundingPoly
{
        std::vector<struct vertice>  vertices;
};


/**
 * struct position
 */
struct position
{
    double x;
    double y;
    double z;
};


/**
 struct landmark
 */
struct landmark
{
    std::string type;
    struct position pos;
};


/**
 * struct faceAnnotation
 */
struct faceAnnotation
{
   double rollAngle;
    double panAngle;
    double tiltAngle;
    double detectionConfidence;
    double landmarkingConfidence;
    
    std::string joyLikelihood;
    std::string sorrowLikelihood;
    std::string angerLikelihood;
    std::string surpriseLikelihood;
    std::string underExposedLikelihood;
    std::string blurredLikelihood;
    std::string  headwearLikelihood;

    struct boundingPoly bounding_poly;
    struct fdBoundingPoly fd_bounding_poly;
    std::vector<struct landmark> landmarks;
};


// prototype
  std::vector<struct faceAnnotation> parseResponseJson(std::string json_text);
void print_annotation(struct faceAnnotation  a);
std::vector<struct vertice> parse_vertices( nlohmann::json  j_vertices);
std::vector<struct landmark> parse_landmarks( nlohmann::json  j_landmarks);
int get_int( nlohmann::json jobj, std::string name);
double get_double(  nlohmann::json jobj, std::string name);
std::string get_string( nlohmann::json jobj, std::string name);
void print_vertices( std::vector<struct vertice> vertices);

using json = nlohmann::json;


/**
 * parse_vertices
 */
std::vector<struct vertice> parse_vertices(nlohmann::json  j_vertices)
{
    std::vector<struct vertice> vec;

    if(  j_vertices.is_array() ) {
    for (  auto j_vertice: j_vertices )
    {
        struct vertice v;
        v.x =  get_int( j_vertice, "x" );
        v.y = get_int( j_vertice, "y" );
        vec.push_back(v);
    } // for vertices
    } // if

    return vec;
}


/**
 * parse_landmarks
 */
std::vector<struct landmark> parse_landmarks(json  j_landmarks)
{
    std::vector<struct landmark> vec;

    if(  j_landmarks.is_array() ) {
    for (  auto j_landmark:   j_landmarks ) 
{
        std::string type = get_string( j_landmark, "type" );
        json j_position = j_landmark["position"];
 
        struct position pos;

        if( j_position.is_object() )
        {
            pos.x =  get_double(j_position, "x" );
            pos.y = get_double(j_position, "y" );       
            pos.z = get_double(j_position, "z" );
        } // if

        struct landmark land;
        land.type = type;
        land.pos = pos;

        vec.push_back(land);
    } // for landmark
    } // if

    return vec;
}


/**
 * get_int
 */
int get_int( json jobj, std::string name)
{
    int value = 0;
    json jname = jobj[name];
    if( jname.is_number() ){
        value =  jname.get<int>();
    }
    return value;
}


/**
 * get_double
 */
double get_double( json jobj, std::string name)
{
    double value = 0;
    json jname = jobj[name];
    if( jname.is_number() ){
        value =  jname.get<double>();
    }
    return value;
}


/**
 * get_string
 */
std::string get_string( json jobj, std::string name)
{
    std::string str = "";
    json jname = jobj[name];
    if( jname.is_string() ){
        str =  jname.get<std::string>();
    }
    return str;
}


/**
 * parseResponseJson
 */
  std::vector<struct faceAnnotation> parseResponseJson(std::string json_text)
{
    std::vector<struct faceAnnotation>  vec;

    json root = json::parse(json_text);
    if( root.is_null() ) {
            std::cout << "not found root" << std::endl;
        return vec;
    }

    json j_responses = root["responses"];

     if( j_responses.is_null() ) {
            std::cout << "not found esponses" << std::endl;
        return vec;
    } 

        json j_response = j_responses[0];
     if( j_response.is_null() ) {
            std::cout << "not found esponses" << std::endl;
        return vec;
    } 

         json j_faceAnnotations = j_response["faceAnnotations"];

         if( j_faceAnnotations.is_null() ) {
                   std::cout << "not found faceAnnotations " << std::endl;
            return vec;
        }
 

    if( j_faceAnnotations.is_array() ) {
    for ( auto j_faceAnnotation: j_faceAnnotations )
{
        struct faceAnnotation annotation;
      
    annotation.rollAngle = 
        get_double(j_faceAnnotation, "rollAngle");

    annotation.panAngle = 
        get_double(j_faceAnnotation, "panAngle");

annotation.tiltAngle = 
        get_double(j_faceAnnotation, "tiltAngle");

   annotation.detectionConfidence = 
        get_double(j_faceAnnotation, "detectionConfidence");

annotation.landmarkingConfidence = 
        get_double(j_faceAnnotation, "landmarkingConfidence");

      annotation.joyLikelihood  =
        get_string(j_faceAnnotation, "joyLikelihood");

     annotation.angerLikelihood  =
        get_string(j_faceAnnotation, "angerLikelihood");

     annotation.surpriseLikelihood  =
        get_string(j_faceAnnotation, "surpriseLikelihood");

     annotation.underExposedLikelihood  =
        get_string(j_faceAnnotation, "underExposedLikelihood");

    annotation.headwearLikelihood  =
        get_string(j_faceAnnotation, "headwearLikelihood");

    annotation.sorrowLikelihood  =
        get_string(j_faceAnnotation, "sorrowLikelihood");

    annotation.blurredLikelihood  =
        get_string(j_faceAnnotation, "blurredLikelihood");


        json j_boundingPoly = j_faceAnnotation["boundingPoly"];

    if( j_boundingPoly.is_null() ) {
            std::cout << "not found boundingPoly" << std::endl;
        }

        json j_vertices = j_boundingPoly["vertices"];
    if( j_vertices.is_null() ) {
            std::cout << "not found vertices" << std::endl;
        }

        auto vertices = parse_vertices(j_vertices);
        annotation.bounding_poly.vertices = vertices;

        json j_fdBoundingPoly = j_faceAnnotation["fdBoundingPoly"];

         if(  j_fdBoundingPoly.is_null() ) {
            std::cout << "not found fdBoundingPoly" << std::endl;
        }

        json j_vertices2 = j_fdBoundingPoly["vertices"];
        if(  j_vertices2.is_null() ) {
            std::cout << "not found vertices2" << std::endl;
        }

        auto vertices2 = parse_vertices(j_vertices2);
        annotation.fd_bounding_poly.vertices = vertices2;


        json j_landmarks = j_faceAnnotation["landmarks"];
        if(  j_landmarks.is_null() ) {
            std::cout << "not found landmarks" << std::endl;
        } 
      
    auto landmarks = parse_landmarks( j_landmarks);
    annotation.landmarks = landmarks;

        vec.push_back(annotation);
    } // for  j_faceAnnotation

    } // if

    return vec;
}


/**
 * print_vertices
 */
void print_vertices( std::vector<struct vertice> vertices)
{
    for( auto v: vertices) 
    {
        std::cout << "x: " << v.x 
        << ", y: " << v.y << std::endl;
    } // for
}


/**
 * print_annotation
 */
void print_annotation(struct faceAnnotation  a)
{
    struct boundingPoly;
    struct fdBoundingPoly;
    struct landmarks;

std::cout << std::endl;
std::cout << "rollAngle: " << a.rollAngle << std::endl;
std::cout << " panAngle: " << a. panAngle  << std::endl;
std::cout << "tiltAngle: " << a.tiltAngle  << std::endl;
std::cout << "detectionConfidence: " << a.detectionConfidence  << std::endl;
std::cout << "landmarkingConfidence: " << a.landmarkingConfidence  << std::endl;

std::cout << " joyLikelihood: " << a. joyLikelihood  << std::endl;
std::cout << "sorrowLikelihood: " << a.sorrowLikelihood  << std::endl;
std::cout << "angerLikelihood: " << a.angerLikelihood  << std::endl;
std::cout << "surpriseLikelihood: " << a.surpriseLikelihood  << std::endl;

std::cout << "underExposedLikelihood: " << a.underExposedLikelihood  << std::endl;

std::cout << "blurredLikelihood: " << a.blurredLikelihood  << std::endl;
std::cout << "headwearLikelihood: " << a.headwearLikelihood  << std::endl;

std::cout << "boundingPoly" << std::endl;
print_vertices( a.bounding_poly.vertices );

std::cout << "fd_boundingPoly" << std::endl;
print_vertices( a.fd_bounding_poly.vertices );

    for(auto landmark:  a.landmarks)
    {
        std::cout << landmark.type << std::endl;
        auto p = landmark.pos;
        std::cout << "x: " << p.x
        << ", y: " << p.y 
        << ", z: " << p.z << std::endl;
    } // for

    std::cout << std::endl;
}

