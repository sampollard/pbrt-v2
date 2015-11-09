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

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef PBRT_TEXTURES_BEZIER_H
#define PBRT_TEXTURES_BEZIER_H

// textures/bezier.h*
#include "pbrt.h"
#include "texture.h"
#include "paramset.h"
#include "montecarlo.h"
#include "shape.h"
#include "parallel.h"
#include "progressreporter.h"

// BezierTexture Declarations
template <typename T> class Bezier2DTexture : public Texture<T> {
public:
    // Bezier2DTexture Public Methods
    Bezier2DTexture(TextureMapping2D *m, Reference<Texture<T> > c1,
                    Reference<Texture<T> > c2,
                    float cp0u, float cp0v, float cp1u, float cp1v,
                    float cp2u, float cp2v, float cp3u, float cp3v)
        : mapping(m), tex1(c1), tex2(c2) {
        cpuv[0][0] = cp0u; cpuv[0][1] = cp0v;
        cpuv[1][0] = cp1u; cpuv[1][1] = cp1v;
        cpuv[2][0] = cp2u; cpuv[2][1] = cp2v;
        cpuv[3][0] = cp3u; cpuv[3][1] = cp3v;
    }

    ~Bezier2DTexture() {
        delete mapping;
    }
    T Evaluate(const DifferentialGeometry &dg) const {
        float s, t, dsdx, dtdx, dsdy, dtdy;
        mapping->Map(dg, &s, &t, &dsdx, &dtdx, &dsdy, &dtdy);
        if (insideCurve(s, t))
            return tex1->Evaluate(dg);
        return tex2->Evaluate(dg);
    }
private:
    // Bezier2DTexture Private Data
    TextureMapping2D *mapping;
    Reference<Texture<T> > tex1, tex2;
    float cpuv[4][2];
    // Compute the bezier curve at time t
    float *bezier(float t) const {
        if (t < 0.f || t > 1.f)
            Warning("t is not in [0,1]");
        return float[2] = {(1-t)*(1-t)*(1-t)};
    }
    // Determine if a texture coordinate is inside of bezier curve
    bool insideCurve(float u, float v) const {
        // Perform a binary search to find the value of t which minimizes
        // the distance to (u,v)
        float min_d = INFINITY;
        float min_t = 0.f;
        float eps = 0.5;
        int octaves = 6;
        for (int i = 0; i < octaves; i++) {

        }

        if (min_d < eps)
            return false;
        else
            return true;
    }
};

Texture<float> *CreateBezierFloatTexture(const Transform &tex2world,
        const TextureParams &tp);

Texture<Spectrum> *CreateBezierSpectrumTexture(const Transform &tex2world,
        const TextureParams &tp);

#endif // PBRT_TEXTURES_BEZIER_H
