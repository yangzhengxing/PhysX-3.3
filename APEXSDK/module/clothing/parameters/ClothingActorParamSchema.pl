{
    header =>
    {
        # Name of the class that will be generated
        className => 'ClothingActorParam',

        # If true, will autogenerate the storage for all the data, otherwise
        # the user will have to implement the raw(Get|Set)XXX() methods, and
        # allocate storage for the parameters himself.  Defaults to true.
        implementStorage => '1',

        # Version History
        # 0.0   Started Parameterization in APEX 1.0
        # 0.1   Added Morph Targets to ActorDesc
        # 0.2   Added physical mesh morph displacements to ActorDesc
        # 0.3   Added possibility to not use adaptive simulation frequency
        # 0.4   CorrectSimulationNormals has been added to the flags
        # 0.5   VelocityClamping has been added
        # 0.6   No more Parallel PhysX- and MeshMesh Skinning
        # 0.7   Added pressure
        # 0.8   Added multiplyGlobalPoseIntoBones (needed for non-reseting teleport)
        # 0.9   Added material overrides.?
        # 0.10  Added simulation backend, so far not used yet
        # 0.11  Added option to freeze clothing when turned off by lod
        # 0.12  Added graphical mesh morph displacements to ActorDesc
        # 0.13  Added option for local space sim
        # 0.14	Store buffered teleport state in actorDesc
        # 0.15	Added RecomputeTangents flag
		# 0.16	Added flags ComputeRenderData and ComputePhysicsMeshNormals to disable when doing external skinning
		# 0.17	Removed useStiffSolver

        # bump this version if something changes!
        classVersion => '0.17',
    },

    structs =>
    [
        {
            name => 'GroupsMask',
            parameters =>
            [
                {
                    name => 'bits0',
                    type => 'U32',
                    defaultValue => '0',
        			hints =>
        			{
        				shortDescription => 'First part of 128-bit group mask',
        			},
                },
                {
                    name => 'bits1',
                    type => 'U32',
                    defaultValue => '0',
        			hints =>
        			{
        				shortDescription => 'Second part of 128-bit group mask',
        			},
                },
                {
                    name => 'bits2',
                    type => 'U32',
                    defaultValue => '0',
        			hints =>
        			{
        				shortDescription => 'Third part of 128-bit group mask',
        			},
                },
                {
                    name => 'bits3',
                    type => 'U32',
                    defaultValue => '0',
        			hints =>
        			{
        				shortDescription => 'Fourth part of 128-bit group mask',
        			},
                },
            ],
        },

        {
            name => 'LODWeights',
            parameters =>
            [
                {
                    name => 'maxDistance',
                    type => 'F32',
                    defaultValue => '2000',
        			hints =>
        			{
        				shortDescription => 'Maximum distance',
        			},
                },
                {
                    name => 'distanceWeight',
                    type => 'F32',
                    defaultValue => '1',
        			hints =>
        			{
        				shortDescription => 'Distance weight',
        			},
                },
                {
                    name => 'bias',
                    type => 'F32',
                    defaultValue => '0',
        			hints =>
        			{
        				shortDescription => 'Bias',
        			},
                },
                {
                    name => 'benefitsBias',
                    type => 'F32',
                    defaultValue => '0',
        			hints =>
        			{
        				shortDescription => 'Benefits bias',
        			},
                },
            ],
        },

        {
            name => 'ClothDescTemplate',
            parameters =>
            [
                {
                    name => 'collisionResponseCoefficient',
                    type => 'F32',
                    defaultValue => '0.2',
                    hints =>
                    {
                        shortDescription => 'Defines a factor for the impulse transfer from cloth to colliding rigid bodies.',
                        longDescription => 'This is only needed if the twoway interaction flag is set in the clothing asset.',
                    },
                },

                {
                    name => 'collisionGroup',
                    type => 'U16',
                    defaultValue => '0',
                    hints =>
                    {
                        shortDescription => 'Sets which collision group this cloth is part of.',
                    },
                },

                {
                    name => 'groupsMask',
                    type => 'GroupsMask',
                    hints =>
                    {
                        shortDescription => 'Sets the 128-bit mask used for collision filtering.',
                    },
                },

                {
                    name => 'validBounds',
                    type => 'BOUNDS3',
                    defaultValue => 'physx::PxVec3(PX_MAX_F32), physx::PxVec3(-PX_MAX_F32)',
                    hints =>
                    {
                        shortDescription => 'Defines the volume outside of which cloth particle are automatically removed from the simulation. ',
                        longDescription => 'Only works if the flag NX_CLF_VALIDBOUNDS is set.',
                    },
                },

                {
                    name => 'compartment',
                    type => 'U64',
                    defaultValue => '0',
                    hints =>
                    {
                        editorDisplay => 'false',
                        shortDescription => 'The compartment to place the cloth in.',
                        longDescription => << 'END',
Must be either a pointer to an NxCompartment of type NX_SCT_CLOTH or
NX_SCT_SOFTBODY, or NULL. A NULL compartment means creating NX_CLF_HARDWARE
cloth in the first available cloth compartment (a default cloth compartment
is created if none exists). Software cloth with a NULL compartment is
created in the scene proper.
END
                    },
                },

                {
                    name => 'userData',
                    type => 'U64',
                    hints =>
                    {
                        editorDisplay => 'false',
                        shortDescription => 'Optional user data pointer.',
                    },
                },
            ],
        },

        {
            name => 'ShapeDescFlags',
            parameters =>
            [
                {
                    name => 'NX_SF_VISUALIZATION',
                    type => 'BOOL',
                    defaultValue => 'true',
                    hints =>
                    {
                        shortDescription => 'Enable debug renderer for this shape'
                    },
                },

                {
                    name => 'NX_SF_DISABLE_COLLISION',
                    type => 'BOOL',
                    defaultValue => 'false',
                    hints =>
                    {
                        shortDescription => 'Disable collision detection for this shape (counterpart of NX_AF_DISABLE_COLLISION)',
                    },
                },

                {
                    name => 'NX_SF_DISABLE_RAYCASTING',
                    type => 'BOOL',
                    defaultValue => 'true',
                    hints =>
                    {
                        shortDescription => 'Disable raycasting for this shape',
                    },
                },

                {
                    name => 'NX_SF_DYNAMIC_DYNAMIC_CCD',
                    type => 'BOOL',
                    defaultValue => 'false',
                    hints =>
                    {
                        shortDescription => 'Enable dynamic-dynamic CCD for this shape. Used only when CCD is globally enabled and shape have a CCD skeleton.',
                    },
                },

                {
                    name => 'NX_SF_DISABLE_SCENE_QUERIES',
                    type => 'BOOL',
                    defaultValue => 'false',
                    hints =>
                    {
                        shortDescription => 'Disable participation in ray casts, overlap tests and sweeps.',
                        longDescription => 'Setting this to true will make the non-compartment CPU cloth not work.',
                    },
                },

            ],
        },

        {
            name => 'ShapeDescTemplate',
            parameters =>
            [
                {
                    name => 'flags',
                    type => 'ShapeDescFlags',
        			hints =>
        			{
        				shortDescription => 'Shape description flags',
        			},
                },

                {
                    name => 'collisionGroup',
                    type => 'U16',
                    defaultValue => '0',
                    hints =>
                    {
                        shortDescription => 'Sets which collision group this shape is part of.',
                        longDescription => << 'END',
Default group is 0. Maximum possible group is 31. Collision groups are sets
of shapes which may or may not be set to collision detect with each other;
this can be set using NxScene::setGroupCollisionFlag()
Sleeping: Does NOT wake the associated actor up automatically.
END
                    },
                },
                {
                    name => 'groupsMask',
                    type => 'GroupsMask',
                    hints =>
                    {
                        shortDescription => 'Sets the 128-bit mask used for collision filtering.',
                    },
                },
                {
                    # PH: Candidate for removal!
                    name => 'materialIndex',
                    type => 'U16',
                    defaultValue => '0',
                    hints =>
                    {
                        shortDescription => 'The material index of the shape.',
                    },
                },

                {
                    name => 'userData',
                    type => 'U64',
                    defaultValue => '0',
                    hints =>
                    {
                        editorDisplay => 'false',
                        shortDescription => 'Optional user data pointer',
                    },
                },

                {
                    name => 'name',
                    type => 'U64',
                    defaultValue => '0',
                    hints =>
                    {
                        editorDisplay => 'false',
                        shortDescription => 'Name of the shapes; must be set by the application and must be a persistent pointer.',
                    },
                },
            ],
        },

        {
            name => 'ActorDescTemplate',
            parameters =>
            [
                {
                    name => 'userData',
                    type => 'U64',
                    defaultValue => '0',
                    hints =>
                    {
                        editorDisplay => 'false',
                        shortDescription => 'Optional user data pointer',
                    },
                },

                {
                    name => 'name',
                    type => 'U64',
                    defaultValue => '0',
                    hints =>
                    {
                        editorDisplay => 'false',
                        shortDescription => 'Optional name string for the shape; must be set by the application and must be a persistent pointer.',
                    },
                },
            ],
        },

        {
            name => 'WindParameters',
            parameters =>
            [
                {
                    name => 'Velocity',
                    type => 'VEC3',
                    defaultValue => '0.0f',
                    hints =>
                    {
                        shortDescription => 'The target velocity each vertex tries to achieve.',
                    },
                },

                {
                    name => 'Adaption',
                    type => 'F32',
                    defaultValue => '0.0f',
                    hints =>
                    {
                        shortDescription => 'The rate of adaption. The higher this value, the faster the cloth reaches the wind velocity. Set to 0 to turn off wind.',
                        longDescription => 'This is roughly the inverse of the time in seconds it takes to adapt to the wind velocity.'
                    },
                },
            ],
        },

        {
            name => 'MaxDistanceScale',
            parameters =>
            [
                {
                    name => 'Scale',
                    type => 'F32',
                    defaultValue => '1.0f',
        			hints =>
        			{
        				shortDescription => 'Scale',
        			},
                },

                {
                    name => 'Multipliable',
                    type => 'BOOL',
                    defaultValue => 'false',
        			hints =>
        			{
        				shortDescription => 'Multipliable',
        			},
                },
            ],
        },

        {
            name => 'ClothingActorFlags',
            parameters =>
            [
                {
                    name => 'ParallelCpuSkinning',
                    type => 'BOOL',
                    defaultValue => 'true',
                    hints =>
                    {
                        shortDescription => 'Determines whether or not to perform CPU skinning in parallel',
                        longDescription => << 'END',
All graphical vertices without correspondence to physical vertices or
triangles are skinned normally. This flag specifies whether this happens
during Physics scene simulation, or after.
Note: If this flag is set, an inconsistency can arise when calling
NxClothingActor::updateRenderResource in between NxApexScene::simulate
and NxApexScene::fetchResults. As a workaround, you should only call
NxClothingActor::updateRenderResources _after_ NxApexScene::fetchResults
has terminated.
END
                    },
                },

                {
                    name => 'RecomputeNormals',
                    type => 'BOOL',
                    defaultValue => 'false',
                    hints =>
                    {
                        shortDescription => 'Fully recomputes the normals on the final mesh.',
                        longDescription => << 'END',
This usually leads to better looking results, but is more expensive to
compute. Default is off.
END
                    },
                },

                {
                    name => 'RecomputeTangents',
                    type => 'BOOL',
                    defaultValue => 'false',
                    hints =>
                    {
                        shortDescription => 'Fully recomputes the tangents on the final mesh.',
                        longDescription => << 'END',
RecomputeTangents can only be set to false if less than half of the graphics mesh vertices have an exact
match in the physics mesh. Otherwise it's always on.
END
                    },
                },

                {
                    name => 'Visualize',
                    type => 'BOOL',
                    defaultValue => 'true',
                    hints =>
                    {
                        shortDescription => 'Determines whether or not to display debug visualization for this clothing actor',
                    },
                },

                {
                    name => 'CorrectSimulationNormals',
                    type => 'BOOL',
                    defaultValue => 'true',
                    hints =>
                    {
                        shortDescription => '',
                        longDescription => << 'END',
The MaxDistance=0 vertices can have a perturbed simulation normal. This usually
happens only for meshes where the MaxDistance=0 vertices are somewhere in the
middle separating a simulated and non-simulated region. The normal for those
vertices will be computed only by the simulated triangles which can lead to
wrong results.
This solution will use the normals from the original simulation mesh and skin
them with respect to the local pose.
END
                    },
                },

                {
					name => 'ComputeRenderData',
                    type => 'BOOL',
                    defaultValue => 'true',
                    hints =>
                    {
                        shortDescription => 'If set to false no skinning is done for this actor. Disable if all skinning is done outside of APEX.',
                    },
                },

                {
					name => 'ComputePhysicsMeshNormals',
                    type => 'BOOL',
                    defaultValue => 'true',
                    hints =>
                    {
                        shortDescription => 'If set to false the normals on the physics mesh are not computed. Disable skinning and normal calculation is done outside of APEX.',
                    },
                }
            ],
        },
    ],

    parameters =>
    [
        {
            name => 'globalPose',
            type => 'MAT44',
            defaultValue => 'physx::PxVec4(1.0f)', # will initialize it to the identity
            hints =>
            {
                editorDisplay => 'false',
                shortDescription => 'The pose where the clothing asset will be put into the scene',
            },
        },

        {
            name => 'useHardwareCloth',
            type => 'BOOL',
            defaultValue => 'true',
            hints =>
            {
                shortDescription => 'Turns on hardware acceleration for the cloth simulation',
            },
        },

        {
            name => 'flags',
            type => 'ClothingActorFlags',
            hints =>
            {
                shortDescription => 'A selection of flags, can be updated at runtime.',
            },
        },

        {
            name => 'fallbackSkinning',
            type => 'BOOL',
            defaultValue => 'false',
            hints =>
            {
                shortDescription => 'Performs skinning in software',
                longDescription => << 'END',
Performs the regular boneweighted skinning on the CPU before giving the
data out through the rendering API.
END
            },
        },

        {
            name => 'slowStart',
            type => 'BOOL',
            defaultValue => 'true',
            hints =>
            {
                shortDescription => 'Prevents from having full max distance right from the start',
                longDescription => << 'END',
The first time a NxClothingActor starts to be simulated is with full max
distance. This prevents starting with full max distance and instead blending
in as it will do the second time.
END
            },
        },

        {
            name => 'useInternalBoneOrder',
            type => 'BOOL',
            defaultValue => 'false',
            hints =>
            {
                editorDisplay => 'false',
                shortDescription => 'Expect internally ordered bone arrays in updateState call.',
                longDescription => << 'END',
If this is set to true the bone buffers in updateState and the actor
descriptor have to be given in the same order as the bones are stored
internally in the asset. This can be queried using
NxClothingAsset::getNumUsedBones and NxClothingAsset::getBoneName or
NxClothingAsset::getBoneMapping.

If this is set to false, the bone buffers can be provided in the order as
they are stored in the application. This is either the bone order at
authoring time, or NxClothingAsset::remapBoneIndex can be called for each
bone to let APEX know about the current ordering in the game. Note that
this is only recommended if the application already uses physx::PxMat44
(or something binary equivalent) and does not have to convert the matrices.
END

            },
        },

        {
            name => 'updateStateWithGlobalMatrices',
            type => 'BOOL',
            defaultValue => 'false',
            hints =>
            {
                shortDescription => 'Use world space matrices instead of composite (relative to bind pose) in NxClothingActor::updateState().',
                longDescription => << 'END',
Depending on what matrices are present, the state can be updated using
global world or object space bone matrices or composite matrices. The
composite matrix can be generated by multiplying the world or object space
matrix by the inverse bone bine pose.

Note: If there are problems which might be caused by bind poses being
different in the ClothingAsset and in the game's animation system, changing
this to true (and thus providing global pose matrices) might fix the problem.
END
            },
        },

        {
            name => 'uvChannelForTangentUpdate',
            type => 'U32',
            defaultValue => '0',
            hints =>
            {
                shortDescription => 'This UV channel is used for updating tangent space',
                longDescription => << 'END',
Tangent update is done based on one UV channel. This allows selection of what
UV channel is being used.
END
            },
        },

        {
            name => 'maxDistanceBlendTime',
            type => 'F32',
            defaultValue => '1.0',
            hints =>
            {
                shortDescription => 'Time in seconds how long it takes to go from zero maxDistance to full maxDistance',
                longDescription => 'Note: This also influences how quickly different physical LoDs can be switched',
            },
        },

        {
            name => 'clothingMaterialIndex',
            type => 'U32',
            defaultValue => '0',
            hints =>
            {
                shortDescription => 'Use this material from the assets material library',
            },
        },

        {
            name => 'lodWeights',
            type => 'LODWeights',
        },

        {
            name => 'windParams',
            type => 'WindParameters',
            hints =>
            {
                shortDescription => 'The per-actor wind parameters',
            },
        },

        {
            name => 'maxDistanceScale',
            type => 'MaxDistanceScale',
   			hints =>
   			{
   				shortDescription => 'Maximum distance scale',
   			},
        },

        {
            name => 'userData',
            type => 'U64',
            defaultValue => '0',
            hints =>
            {
                editorDisplay => 'false',
                shortDescription => 'Optional user data pointer associated with the clothing actor',
            },
        },

        {
            name => 'boneMatrices',
            type => 'MAT44',
            isArray => '1',
            arraySize => '-1',
            hints =>
            {
                editorDisplay => 'false',
                shortDescription => 'An Array of matrices with the full transform for each bone',
                longDescription => << 'END',
These matrices are sometimes referred to as composite matrices. They are the
multiplication of the current world space bone pose with the inverse bind
pose in world space.
Note: If \'updateStateWithGlobalMatrices\' is set to true, these must be
global poses instead.
END
            },
        },

        {
            name => 'clothDescTemplate',
            type => 'ClothDescTemplate',
            hints =>
            {
                shortDescription => 'Contains the parameters the application can override on the NxClothDesc when created',
            },
        },

        {
            name => 'shapeDescTemplate',
            type => 'ShapeDescTemplate',
            hints =>
            {
                shortDescription => 'Contains the parameters the application can override on any actor shapes created',
            },
        },

        {
            name => 'actorDescTemplate',
            type => 'ActorDescTemplate',
            hints =>
            {
                shortDescription => 'Contains the parameters the application can override on any actors created',
            },
        },

        {
            name => 'actorScale',
            type => 'F32',
            defaultValue => '1.0',
            hints =>
            {
                shortDescription => 'Scales the actor relative to the asset.',
				longDescription => << 'END',
Setting globalPose doesn't change the actor scale, actorScale should be set separately.
END
            },
        },

        {
            name => 'runtimeCooked',
            type => 'REF',
            classNames => [ qw ( ClothingCookedParam ) ],
            hints =>
            {
                INCLUDED => '1',
                shortDescription => 'Data cooked at runtime',
            },
        },

        {
            name => 'morphDisplacements',
            type => 'VEC3',
            isArray => '1',
            arraySize => '-1',
            hints =>
            {
                shortDescription => 'Displacements according to the current morph target.',
            },
        },

        {
            name => 'morphPhysicalMeshNewPositions',
            type => 'VEC3',
            isArray => '1',
            arraySize => '-1',
            hints =>
            {
                shortDescription => 'New positions for the physical meshes and convex collision volumes.',
            },
        },

        {
            name => 'morphGraphicalMeshNewPositions',
            type => 'VEC3',
            isArray => '1',
            arraySize => '-1',
            hints =>
            {
                shortDescription => 'New positions of all submeshes of all graphical meshes.',
            },
        },

        {
            name => 'allowAdaptiveTargetFrequency',
            type => 'BOOL',
            defaultValue => 'true',
            hints =>
            {
                shortDescription => 'Slightly modifies gravity to avoid high frequency jittering due to variable time steps.',
            },
        },

        {
            name => 'useVelocityClamping',
            type => 'BOOL',
            defaultValue => 'false',
   			hints =>
   			{
   				shortDescription => 'Enable/disable velocity clamping',
   			},
        },

        {
            name => 'vertexVelocityClamp',
            type => 'BOUNDS3',
            defaultValue => 'physx::PxVec3(-PX_MAX_F32), physx::PxVec3(PX_MAX_F32)',
   			hints =>
   			{
   				shortDescription => 'Vertex velocity clamping values',
   			},
        },

        {
            name => 'pressure',
            type => 'F32',
            defaultValue => '-1.0',
            hints =>
            {
                shortDescription => 'Set pressure of cloth, only works on closed meshes.'
            },
        },

        {
            name => 'multiplyGlobalPoseIntoBones',
            type => 'BOOL',
            defaultValue => 'true',
   			hints =>
   			{
   				shortDescription => 'Enable/disable multiplying global pose into bones',
   			},
        },

        {
            name => 'overrideMaterialNames',
            type => 'STRING',
            isArray => '1',
            arraySize => '-1',
            hints =>
            {
                shortDescription => 'Replacement material names for the ones provided by the render mesh asset inside the clothing asset.',
            },
        },

        {
            name => 'simulationBackend',
            type => 'ENUM',
            enumVals => [ qw(Default ForceNative ForceEmbedded) ],
            defaultValue => '"Default"',
            hints =>
            {
                shortDescription => 'Select which backend should be used. \'ForceNative\' will only work when running with the 2.8.x PhysX SDK',
            },
        },

        {
            name => 'freezeByLOD',
            type => 'BOOL',
            defaultValue => 'false',
            hints =>
            {
                shortDescription => 'Cloth state frozen when LoD turns off simulation of the actor, instead of returning to the animated state.',
            },
        },

        {
            name => 'localSpaceSim',
            type => 'BOOL',
            defaultValue => 'false',
            hints =>
            {
                shortDescription => 'Do simulation in local space.',
                longDescription => << 'END',
If this flag is enabled the simulation is done at origin, however the cloth is rendered at its global position.
The simulation of the actor is transformed such that the root bone ends up at origin. The scale of the actor is maintained during the simulation.
If a 3.x physX simulation backend is used, it is possible to add the inertia effects to the simulation, through
the inertiaScale parameter of the clothing material. So with an inertiaScale of 1.0 there should be no visible
difference between local space and global space simulation.
Known issues:
- PhysX 2.8.4 does not support inertiaScale (it corresponds to inertiaScale=0.0f). So if localSpaceSim is enabled there's no inertia effect when the global pose of the clothing actor changes.
- With 2.8.4 this only works for clothing on 1 character, without world collision. This is because collision volumes would interfere with the cloth that is simulated at origin.
This is not a problem in 3.x because there collision only happens with the collision volumes specifically defined for the clothing actor.
END
            },
        },

        {
			name => 'teleportMode',
			type => 'I32',
			defaultValue => '0',
			hints =>
			{
				shortDescription => 'Buffered teleport state for the next simulate call, gets set in updateState, is reset to Continuous during simulate().',
                longDescription => << 'END',
0 = ClothingTeleportMode::Continuous
1 = ClothingTeleportMode::Teleport
2 = ClothingTeleportMode::TeleportAndReset
END
			},
        },
    ]
};
