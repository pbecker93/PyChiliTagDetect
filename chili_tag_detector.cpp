#include <iostream>
#include <Python.h>
#include <numpy/ndarrayobject.h>
#include <stdio.h>
#include <chilitags.hpp>
#include <opencv2/highgui/highgui.hpp> 
//Actual module method definition - this is the code that will be called by
//hello_module.print_hello_world

static PyObject* detect(PyObject *self, PyArrayObject *img)
{
    import_array() 

    int rows = PyArray_SHAPE(img)[0];
    int cols = PyArray_SHAPE(img)[1];
    void *frame_data = PyArray_DATA(img);
	
    cv::Mat image(rows, cols, CV_8UC3, frame_data);
    PyObject* list = PyList_New(0);
    if(image.data) {

        for (const auto &tag : chilitags::Chilitags().find(image)) {
            chilitags::Quad corners = tag.second;

            PyObject* t = PyTuple_New(2);
            PyTuple_SetItem(t, 0, PyLong_FromLong(tag.first));
            int nd = 2;
            npy_intp dims[] = {4, 2}; 
	    PyObject *coords = PyArray_SimpleNew(nd, dims, NPY_FLOAT);
            for(int i = 0; i < 4; ++i){
		for(int j = 0; j < 2; ++j){
			auto p = PyArray_GETPTR2(coords, i, j);
			PyArray_SETITEM(coords, p , PyFloat_FromDouble(corners.val[i * 2 +j]));
	    	}
            }
            PyTuple_SetItem(t, 1, coords);
            PyList_Append(list, t);
        }
        return list;
    }
    return list;
}

//Method definition object for this extension, these argumens mean:
//ml_name: The name of the method
//ml_meth: Function pointer to the method implementation
//ml_flags: Flags indicating special features of this method, such as
//          accepting arguments, accepting keyword arguments, being a
//          class method, or being a static method of a class.
//ml_doc:  Contents of this method's docstring
static PyMethodDef chili_tag_detector_methods[] = { 
    {   
        "detect",
        (PyCFunction)detect,
        METH_O,
        "detect chili tags in given image"
    },  
    {NULL, NULL, 0, NULL}
};

//Module definition
//The arguments of this structure tell Python what to call your extension,
//what it's methods are and where to look for it's method definitions
static struct PyModuleDef chili_tag_detector_definition = { 
    PyModuleDef_HEAD_INIT,
    "chili_tag_detector",
    "A Python wrapper for detecting chili tags in images.",
    -1, 
    chili_tag_detector_methods
};

//Module initialization
//Python calls this function when importing your extension. It is important
//that this function is named PyInit_[[your_module_name]] exactly, and matches
//the name keyword argument in setup.py's setup() call.
PyMODINIT_FUNC PyInit_chili_tag_detector(void)
{
    Py_Initialize();

    return PyModule_Create(&chili_tag_detector_definition);
}
