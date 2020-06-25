/**
 * assimp sample
 * 2020-03-01 K.OHWADA
 */

// draw 3D model from file
// original : https://github.com/assimp/assimp/blob/master/samples/SimpleOpenGL/Sample_SimpleOpenGL.c


/* ----------------------------------------------------------------------------
// Simple sample to prove that Assimp is easy to use with OpenGL.
// It takes a file name as command line parameter, loads it using standard
// settings and displays it.
//
// If you intend to _use_ this code sample in your app, do yourself a favour
// and replace immediate mode calls with VBOs ...
//
// The vc8 solution links against assimp-release-dll_win32 - be sure to
// have this configuration built.
// ----------------------------------------------------------------------------
*/


#include <stdlib.h>
#include <stdio.h>

//#ifdef __APPLE__
//#include <freeglut.h>
//#else
//#include <GL/freeglut.h>
//#endif

//macOS
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

/* assimp include files. These three are usually needed. */
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/version.h>

#define COMMAND_USAGE "--usage"


/**
 *  print_run_command
 */
inline static void print_run_command(const char* command_name) {
	//printf("Run '%s %s' for more information.\n", 
		//PROJECT_NAME, command_name);
	printf("Run '%s' for more information.\n", 
		command_name);
}


/**
 *  print_error
 */
inline static void print_error(const char* msg) {
	printf("ERROR: %s\n", msg);
}


#define NEW_LINE "\n"
#define DOUBLE_NEW_LINE NEW_LINE NEW_LINE


/**
 *  print_usage
 */
inline static void print_usage() {
	static const char* usage_format = "Usage: "
		" <file>" DOUBLE_NEW_LINE
		"where:" DOUBLE_NEW_LINE
		"  %-10s %s" DOUBLE_NEW_LINE
		"options:"	 DOUBLE_NEW_LINE
		"  %-10s %s" DOUBLE_NEW_LINE;

	printf(usage_format,
		// where
		"file", "The input model file to load.",
		// options
		COMMAND_USAGE, "Display usage.");
}


/* the global Assimp scene object */
const struct aiScene* scene = NULL;
GLuint scene_list = 0;

struct aiVector3D scene_min, scene_max, scene_center;

/* current rotation angle */
static float angle = 0.f;

#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)


/**
 *  reshape
 */
void reshape(int width, int height)
{
	const double aspectRatio = (float) width / height, fieldOfView = 45.0;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fieldOfView, aspectRatio,
		1.0, 1000.0);  /* Znear and Zfar */
	glViewport(0, 0, width, height);
}


/**
 *  get_bounding_box_for_node
 */
void get_bounding_box_for_node (const struct aiNode* nd,
	struct aiVector3D* min,
	struct aiVector3D* max,
	struct aiMatrix4x4* trafo
){
	struct aiMatrix4x4 prev;
	unsigned int n = 0, t;

	prev = *trafo;
	aiMultiplyMatrix4(trafo,&nd->mTransformation);

	for (; n < nd->mNumMeshes; ++n) {
		const struct aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];
		for (t = 0; t < mesh->mNumVertices; ++t) {

			struct aiVector3D tmp = mesh->mVertices[t];
			aiTransformVecByMatrix4(&tmp,trafo);

			min->x = aisgl_min(min->x,tmp.x);
			min->y = aisgl_min(min->y,tmp.y);
			min->z = aisgl_min(min->z,tmp.z);

			max->x = aisgl_max(max->x,tmp.x);
			max->y = aisgl_max(max->y,tmp.y);
			max->z = aisgl_max(max->z,tmp.z);
		}
	}

	for (n = 0; n < nd->mNumChildren; ++n) {
		get_bounding_box_for_node(nd->mChildren[n],min,max,trafo);
	}
	*trafo = prev;
}



/**
 *  get_bounding_box
 */
void get_bounding_box(struct aiVector3D* min, struct aiVector3D* max)
{
	struct aiMatrix4x4 trafo;
	aiIdentityMatrix4(&trafo);

	min->x = min->y = min->z =  1e10f;
	max->x = max->y = max->z = -1e10f;
	get_bounding_box_for_node(scene->mRootNode,min,max,&trafo);
}



/**
 *  color4_to_float4
 */
void color4_to_float4(const struct aiColor4D *c, float f[4])
{
	f[0] = c->r;
	f[1] = c->g;
	f[2] = c->b;
	f[3] = c->a;
}


/**
 *  set_float4
 */
void set_float4(float f[4], float a, float b, float c, float d)
{
	f[0] = a;
	f[1] = b;
	f[2] = c;
	f[3] = d;
}



/**
 *  apply_material
 */
void apply_material(const struct aiMaterial *mtl)
{
	float c[4];

	GLenum fill_mode;
	int ret1, ret2;
	struct aiColor4D diffuse;
	struct aiColor4D specular;
	struct aiColor4D ambient;
	struct aiColor4D emission;
	ai_real shininess, strength;
	int two_sided;
	int wireframe;
	unsigned int max;

	set_float4(c, 0.8f, 0.8f, 0.8f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
		color4_to_float4(&diffuse, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, c);

	set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
		color4_to_float4(&specular, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

	set_float4(c, 0.2f, 0.2f, 0.2f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
		color4_to_float4(&ambient, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c);

	set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
		color4_to_float4(&emission, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, c);

	max = 1;
	ret1 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
	if(ret1 == AI_SUCCESS) {
    	max = 1;
    	ret2 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS_STRENGTH, &strength, &max);
		if(ret2 == AI_SUCCESS)
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * strength);
        else
        	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    }
	else {
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
		set_float4(c, 0.0f, 0.0f, 0.0f, 0.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);
	}

	max = 1;
	if(AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_ENABLE_WIREFRAME, &wireframe, &max))
		fill_mode = wireframe ? GL_LINE : GL_FILL;
	else
		fill_mode = GL_FILL;
	glPolygonMode(GL_FRONT_AND_BACK, fill_mode);

	max = 1;
	if((AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_TWOSIDED, &two_sided, &max)) && two_sided)
		glDisable(GL_CULL_FACE);
	else
		glEnable(GL_CULL_FACE);
}



/**
 *  ecursive_render
 */
void recursive_render (const struct aiScene *sc, const struct aiNode* nd)
{
	unsigned int i;
	unsigned int n = 0, t;
	struct aiMatrix4x4 m = nd->mTransformation;

	/* update transform */
	aiTransposeMatrix4(&m);
	glPushMatrix();
	glMultMatrixf((float*)&m);

	/* draw all meshes assigned to this node */
	for (; n < nd->mNumMeshes; ++n) {
		const struct aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];

		apply_material(sc->mMaterials[mesh->mMaterialIndex]);

		if(mesh->mNormals == NULL) {
			glDisable(GL_LIGHTING);
		} else {
			glEnable(GL_LIGHTING);
		}

		for (t = 0; t < mesh->mNumFaces; ++t) {
			const struct aiFace* face = &mesh->mFaces[t];
			GLenum face_mode;

			switch(face->mNumIndices) {
				case 1: face_mode = GL_POINTS; break;
				case 2: face_mode = GL_LINES; break;
				case 3: face_mode = GL_TRIANGLES; break;
				default: face_mode = GL_POLYGON; break;
			}

			glBegin(face_mode);

			for(i = 0; i < face->mNumIndices; i++) {
				int index = face->mIndices[i];
				if(mesh->mColors[0] != NULL)
					glColor4fv((GLfloat*)&mesh->mColors[0][index]);
				if(mesh->mNormals != NULL)
					glNormal3fv(&mesh->mNormals[index].x);
				glVertex3fv(&mesh->mVertices[index].x);
			}

			glEnd();
		}

	}

	/* draw all children */
	for (n = 0; n < nd->mNumChildren; ++n) {
		recursive_render(sc, nd->mChildren[n]);
	}

	glPopMatrix();
}


/**
 *  do_motion
 */
void do_motion (void)
{
	static GLint prev_time = 0;
	static GLint prev_fps_time = 0;
	static int frames = 0;

	int time = glutGet(GLUT_ELAPSED_TIME);
	angle += (float)((time-prev_time)*0.01);
	prev_time = time;

	frames += 1;
	if ((time - prev_fps_time) > 1000) /* update every seconds */
    {
        int current_fps = frames * 1000 / (time - prev_fps_time);
        printf("%d fps\n", current_fps);
        frames = 0;
        prev_fps_time = time;
    }


	glutPostRedisplay ();
}


/**
 *  display
 */
void display(void)
{
	float tmp;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.f,0.f,3.f,0.f,0.f,-5.f,0.f,1.f,0.f);

	/* rotate it around the y axis */
	glRotatef(angle,0.f,1.f,0.f);

	/* scale the whole asset to fit into our view frustum */
	tmp = scene_max.x-scene_min.x;
	tmp = aisgl_max(scene_max.y - scene_min.y,tmp);
	tmp = aisgl_max(scene_max.z - scene_min.z,tmp);
	tmp = 1.f / tmp;
	glScalef(tmp, tmp, tmp);

        /* center the model */
	glTranslatef( -scene_center.x, -scene_center.y, -scene_center.z );

        /* if the display list has not been made yet, create a new one and
           fill it with scene contents */
	if(scene_list == 0) {
	    scene_list = glGenLists(1);
	    glNewList(scene_list, GL_COMPILE);
            /* now begin at the root node of the imported data and traverse
               the scenegraph by multiplying subsequent local transforms
               together on GL's matrix stack. */
	    recursive_render(scene, scene->mRootNode);
	    glEndList();
	}

	glCallList(scene_list);

	glutSwapBuffers();

	do_motion();
}


/**
 *  loadasset
 */
int loadasset (const char* path)
{
	/* we are taking one of the postprocessing presets to avoid
	   spelling out 20+ single postprocessing flags here. */
	scene = aiImportFile(path,aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene) {
		get_bounding_box(&scene_min,&scene_max);
		scene_center.x = (scene_min.x + scene_max.x) / 2.0f;
		scene_center.y = (scene_min.y + scene_max.y) / 2.0f;
		scene_center.z = (scene_min.z + scene_max.z) / 2.0f;
		return 0;
	}
	return 1;
}


/**
 *  getFname
 */
char* getFname(char *filepath)
{
	char* fname = strchr(filepath, '/');
    return &fname[1];
}


/**
 *  createWinTitle
 */
char* createWinTitle(char *filepath)
{
	char* win_title = (char*)malloc(100);

	char* fname1 = getFname(filepath);
	char* fname2 = getFname(fname1);

    strcpy(win_title, "Assimp: ");
	strcat(win_title, fname2);

    return win_title;
}


/**
 *  rintAssimpVersion
 */
void printAssimpVersion()
{
    unsigned int major = aiGetVersionMajor();
    unsigned int minor = aiGetVersionMinor();
    unsigned int rev =  aiGetVersionRevision();

    printf("AssimpVersion: %d.%d.%d \n", major, minor, rev);
}


/**
 *  main
 */
int main(int argc, char **argv)
{
	const int WIN_WIDTH = 900;
	const int WIN_HEIGHT = 600;
	const int WIN_POS_X = 100;
	const int WIN_POS_Y = 100;

	const char* model_file = NULL;
	struct aiLogStream stream;

    printAssimpVersion();

	if (argc < 2) {
		//print_error("No input model file specifed.");
		//print_run_command(COMMAND_USAGE);
			print_usage();
		return EXIT_FAILURE;
	}

	// Find and execute available commands entered by the user.
	for (int i = 1; i < argc; ++i) {
		if (!strncmp(argv[i], COMMAND_USAGE, strlen(COMMAND_USAGE))) {
			print_usage();
			return EXIT_SUCCESS;
		}
	}

	// Check and validate the specified model file extension.
	model_file = argv[1];
	const char* extension = strchr(model_file, '.');
    printf("extension: %s \n", extension);

	if (!extension) {
		print_error("Please provide a file with a valid extension.");
		return EXIT_FAILURE;
	}

	if (AI_FALSE == aiIsExtensionSupported(extension)) {
		print_error("The specified model file extension is currently unsupported in Assimp ");
		return EXIT_FAILURE;
	}

	char* win_title = createWinTitle(model_file);
    printf("win_title: %s \n", win_title);

	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutInitWindowPosition(WIN_POS_X, WIN_POS_Y);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);

	//glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	//glutCreateWindow("Assimp - Very simple OpenGL sample");
	glutCreateWindow(win_title);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	/* get a handle to the predefined STDOUT log stream and attach
	   it to the logging system. It remains active for all further
	   calls to aiImportFile(Ex) and aiApplyPostProcessing. */
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_STDOUT,NULL);
	aiAttachLogStream(&stream);

	/* ... same procedure, but this stream now writes the
	   log messages to assimp_log.txt */
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_FILE,"assimp_log.txt");
	aiAttachLogStream(&stream);

	// Load the model file.
	if(0 != loadasset(model_file)) {
		print_error("Failed to load model. Please ensure that the specified file exists.");
		aiDetachAllLogStreams();
		return EXIT_FAILURE;
	}

	//glClearColor(0.1f,0.1f,0.1f,1.f);
	glClearColor(0.5f, 0.5f, 0.5f, 1.f); // gray

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);    /* Uses default lighting parameters */

	glEnable(GL_DEPTH_TEST);

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_NORMALIZE);

	/* XXX docs say all polygons are emitted CCW, but tests show that some aren't. */
	if(getenv("MODEL_IS_BROKEN"))
		glFrontFace(GL_CW);

	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);

	glutGet(GLUT_ELAPSED_TIME);
	glutMainLoop();

	/* cleanup - calling 'aiReleaseImport' is important, as the library
	   keeps internal resources until the scene is freed again. Not
	   doing so can cause severe resource leaking. */
	aiReleaseImport(scene);

	/* We added a log stream to the library, it's our job to disable it
	   again. This will definitely release the last resources allocated
	   by Assimp.*/
	aiDetachAllLogStreams();
	return EXIT_SUCCESS;
}

