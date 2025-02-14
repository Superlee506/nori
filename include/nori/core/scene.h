/*
    This file is part of Nori, a simple educational ray tracer

    Copyright (c) 2015 by Wenzel Jakob
*/

#pragma once

#include <nori/core/object.h>
#include <nori/core/common.h>
#include <nori/core/bbox.h>

NORI_NAMESPACE_BEGIN

/**
 * \brief Main scene data structure
 *
 * This class holds information on scene objects and is responsible for
 * coordinating rendering jobs. It also provides useful query routines that
 * are mostly used by the \ref Integrator implementations.
 */
class Scene : public NoriObject {
public:
    /// Construct a new scene object
    Scene(const PropertyList &);

    /// Release all memory
    virtual ~Scene();

    /// Return a pointer to the scene's kd-tree
    const Accel *getAccel() const;

    /// Return a pointer to the scene's integrator
    const Integrator *getIntegrator() const;

    /// Return a pointer to the scene's integrator
    Integrator *getIntegrator();

    /// Return a pointer to the scene's camera
    const Camera *getCamera() const;

    /// Return a pointer to the scene's sample generator (const version)
    const Sampler *getSampler() const;

    /// Return a pointer to the scene's sample generator
    Sampler *getSampler();

    /// Return a reference to an array containing all meshes
    const std::vector<Mesh *> &getMeshes() const;

    /// Return a reference to an array containing all emitters  (const version)
    const std::vector<Emitter*> & getEmitters() const;

    /// Return a pointer to the scene's environment emitter  (const version)
    const Emitter * getEnvironmentEmitter() const;

    /// Return a pointer to the scene's environment emitter
    Emitter * getEnvironmentEmitter();

    /// Return a axis-aligned box that bounds the scene
    const BoundingBox3f& getBoundingBox() const;

    /// Return the color of the background;
    Color3f getBackground() const;

    /// Return whether the specified background color is forced to used
    bool getForceBackground() const;

    /**
     * \brief Intersect a ray against all triangles stored in the scene
     * and return detailed intersection information
     *
     * \param ray
     *    A 3-dimensional ray data structure with minimum/maximum
     *    extent information
     *
     * \param its
     *    A detailed intersection record, which will be filled by the
     *    intersection query
     *
     * \return \c true if an intersection was found
     */
    bool rayIntersect(const Ray3f &ray, Intersection &its) const;

    /**
     * \brief Intersect a ray against all triangles stored in the scene
     * and \a only determine whether or not there is an intersection.
     *
     * This method much faster than the other ray tracing function,
     * but the performance comes at the cost of not providing any
     * additional information about the detected intersection
     * (not even its position).
     *
     * \param ray
     *    A 3-dimensional ray data structure with minimum/maximum
     *    extent information
     *
     * \return \c true if an intersection was found
     */
    bool rayIntersect(const Ray3f &ray) const;

    /**
     * \brief Inherited from \ref NoriObject::activate()
     *
     * Initializes the internal data structures (kd-tree,
     * emitter sampling data structures, etc.)
     */
    void activate();

    /// Add a child object to the scene (meshes, integrators etc.)
    void addChild(NoriObject *obj);

    /// Return a string summary of the scene (for debugging purposes)
    std::string toString() const;

    EClassType getClassType() const;

private:
    Color3f m_background;
    bool m_bForceBackground;

    std::vector<Mesh *> m_pMeshes;
    Integrator *m_pIntegrator = nullptr;
    Sampler *m_pSampler = nullptr;
    Camera *m_pCamera = nullptr;
    Accel *m_pAccel = nullptr;
    std::vector<Emitter*> m_pEmitters;
    Emitter * m_pEnvironmentEmitter = nullptr;
    BoundingBox3f m_bBox;
};

NORI_NAMESPACE_END
