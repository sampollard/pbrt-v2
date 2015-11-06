
/*
    pbrt source code Copyright(c) 1998-2012 Matt Pharr and Greg Humphreys.

    This file is part of pbrt.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are
    met:

    - Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.

    - Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
    IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
    TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
    HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    Modification by Sam Pollard, Western Washington University
    pollars at students dot wwu dot edu

 */


// textures/bezier.cpp*
#include "stdafx.h"
#include "textures/bezier.h"

// CheckerboardTexture Method Definitions
Texture<float> *CreateBezierFloatTexture(const Transform &tex2world,
        const TextureParams &tp) {
    int dim = tp.FindInt("dimension", 2);
    if (dim != 2) {
        Error("%d dimensional bezier texture not supported", dim);
        return NULL;
    }
    Reference<Texture<float> > tex1 = tp.GetFloatTexture("tex1", 0.f);
    Reference<Texture<float> > tex2 = tp.GetFloatTexture("tex2", 1.f);
    // Initialize 2D texture mapping _map_ from _tp_
    TextureMapping2D *map = NULL;
    string type = tp.FindString("mapping", "uv");
    if (type == "uv") {
        float su = tp.FindFloat("uscale", 1.);
        float sv = tp.FindFloat("vscale", 1.);
        float du = tp.FindFloat("udelta", 0.);
        float dv = tp.FindFloat("vdelta", 0.);
        map = new UVMapping2D(su, sv, du, dv);
    }
    else if (type == "spherical") map = new SphericalMapping2D(Inverse(tex2world));
    else if (type == "cylindrical") map = new CylindricalMapping2D(Inverse(tex2world));
    else if (type == "planar")
        map = new PlanarMapping2D(tp.FindVector("v1", Vector(1,0,0)),
            tp.FindVector("v2", Vector(0,1,0)),
            tp.FindFloat("udelta", 0.f), tp.FindFloat("vdelta", 0.f));
    else {
        Error("2D texture mapping \"%s\" unknown", type.c_str());
        map = new UVMapping2D;
    }
    // Initialize the control points
    float cp[8];
    cp[0] = tp.FindFloat("cp0u",  0.0); cp[1] = tp.FindFloat("cp0v", 0.0);
    cp[2] = tp.FindFloat("cp1u", -1.0); cp[3] = tp.FindFloat("cp1v", 2.0);
    cp[4] = tp.FindFloat("cp2u",  1.0); cp[5] = tp.FindFloat("cp2v", 2.0);
    cp[6] = tp.FindFloat("cp3u",  1.0); cp[7] = tp.FindFloat("cp3v", 1.0);
    return new Bezier2DTexture<float>(map, tex1, tex2, cp[0], cp[1], cp[2],
                                      cp[3], cp[4], cp[5], cp[6], cp[7]);
}

Texture<Spectrum> *CreateBezierSpectrumTexture(const Transform &tex2world,
        const TextureParams &tp) {
    int dim = tp.FindInt("dimension", 2);
    if (dim != 2) {
        Error("%d dimensional bezier texture not supported", dim);
        return NULL;
    }
    Reference<Texture<Spectrum> > tex1 = tp.GetSpectrumTexture("tex1", 0.f);
    Reference<Texture<Spectrum> > tex2 = tp.GetSpectrumTexture("tex2", 1.f);
    // Initialize 2D texture mapping _map_ from _tp_
    TextureMapping2D *map = NULL;
    string type = tp.FindString("mapping", "uv");
    if (type == "uv") {
        float su = tp.FindFloat("uscale", 1.);
        float sv = tp.FindFloat("vscale", 1.);
        float du = tp.FindFloat("udelta", 0.);
        float dv = tp.FindFloat("vdelta", 0.);
        map = new UVMapping2D(su, sv, du, dv);
    }
    else if (type == "spherical") map = new SphericalMapping2D(Inverse(tex2world));
    else if (type == "cylindrical") map = new CylindricalMapping2D(Inverse(tex2world));
    else if (type == "planar")
        map = new PlanarMapping2D(tp.FindVector("v1", Vector(1,0,0)),
            tp.FindVector("v2", Vector(0,1,0)),
            tp.FindFloat("udelta", 0.f), tp.FindFloat("vdelta", 0.f));
    else {
        Error("2D texture mapping \"%s\" unknown", type.c_str());
        map = new UVMapping2D;
    }
    // Initialize the control points
    float cp[8];
    cp[0] = tp.FindFloat("cp0u",  0.0); cp[1] = tp.FindFloat("cp0v", 0.0);
    cp[2] = tp.FindFloat("cp1u", -1.0); cp[3] = tp.FindFloat("cp1v", 2.0);
    cp[4] = tp.FindFloat("cp2u",  1.0); cp[5] = tp.FindFloat("cp2v", 2.0);
    cp[6] = tp.FindFloat("cp3u",  1.0); cp[7] = tp.FindFloat("cp3v", 1.0);
    return new Bezier2DTexture<Spectrum>(map, tex1, tex2, cp[0], cp[1], cp[2],
                                         cp[3], cp[4], cp[5], cp[6], cp[7]);
}

// Determine if a texture coordinate is inside of bezier curve
bool insideCurve(float u, float v) {
    return false;
}
