/* File : tsne.i */
%module tsne
%include "cpointer.i"
%include pointer.i
%{
/* Put headers and other declarations here */
#include "tsnelib/tsne.h"
#include "tsnelib/quadtree.h"

%}

%include "tsnelib/tsne.h"
%include "tsnelib/quadtree.h"


