/*
Protobyte Library 0.1.6
Ira Greenberg 2016
*/

#include "ProtoPlasm.h"
#include "ProtoController.h"
#include <iostream>

int main(int argc, char const** argv) {
		new ijg::ProtoPlasm (1024, 1200, "ProtoController", new ProtoController());
		return EXIT_SUCCESS;
}