/*
Protobyte Library 0.1.7
Ira Greenberg 2019
*/

#include "ProtoPlasm.h"
#include "ProtoController.h"
#include <iostream>

int main(int argc, char const** argv) {
		new ijg::ProtoPlasm (1330, 1500, "ProtoController", new ProtoController());
		return EXIT_SUCCESS;
}