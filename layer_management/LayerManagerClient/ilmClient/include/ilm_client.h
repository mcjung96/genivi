/***************************************************************************
*
* Copyright 2010,2011 BMW Car IT GmbH
* Copyright (c) 2012, NVIDIA CORPORATION.  All rights reserved.
*
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*        http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
****************************************************************************/
#ifndef _ILM_CLIENT_H_
#define _ILM_CLIENT_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "ilm_types.h"
/**
 * \defgroup ilmClient Layer Management Client API - API which each application(including HMI) has to use. 
 * \defgroup ilmControl Layer Management Control API - Special Control API which has to be used from the HMI/Tooling to control the composition.
 */

/* BEGIN OF CLIENT API */
/**
 * \brief Initializes the IVI LayerManagement Client.
 * \ingroup ilmClient
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if a connection can not be established to the services.
 */
ilmErrorTypes ilm_init();

/**
 * \brief Destroys the IVI LayerManagement Client.
 * \ingroup ilmClient
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not be closed or was not initialized.
 */
ilmErrorTypes ilm_destroy();

/**
 * \brief Get the screen resolution of a specific screen from the Layermanagement
 * \ingroup ilmClient
 * \param[in] screenID Screen Indentifier as a Number from 0 .. MaxNumber of Screens
 * \param[out] pWidth pointer where width of screen should be stored
 * \param[out] pHeight pointer where height of screen should be stored
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not get the resolution.
 */
ilmErrorTypes ilm_getScreenResolution(t_ilm_uint screenID, t_ilm_uint* pWidth, t_ilm_uint* pHeight);

/**
 * \brief Create a surface
 * \ingroup ilmClient
 * \param[in] nativehandle The native windowsystem's handle for the surface
 * \param[in] width The original width of the surface
 * \param[in] height The original height of the surface
 * \param[in] pixelFormat The pixelformat to be used for the surface
 * \param[in] pSurfaceId The value pSurfaceId points to is used as ID for new surface;
 * \param[out] pSurfaceId The ID of the newly created surface is returned in this parameter
 *
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_surfaceCreate(t_ilm_nativehandle nativehandle, t_ilm_int width, t_ilm_int height, ilmPixelFormat pixelFormat, t_ilm_surface *pSurfaceId);

/**
 * \brief Remove a surface
 * \ingroup ilmClient
 * \param[in] surfaceId The id of the surface to be removed
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_surfaceRemove(const t_ilm_surface surfaceId);

/**
 * \brief Set the native content of an application to be used as surface content
 * \ingroup ilmClient
 * \param[in] nativehandle The native windowsystem's handle for the surface
 * \param[in] width The original width of the surface
 * \param[in] height The original height of the surface
 * \param[in] pixelFormat The pixelformat to be used for the surface
 * \param[in] surfaceId The ID of the surface
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_surfaceSetNativeContent(t_ilm_nativehandle nativehandle, t_ilm_int width, t_ilm_int height, ilmPixelFormat pixelFormat, t_ilm_surface surfaceId);

/**
 * \brief Remove the native content of a surface
 * \ingroup ilmClient
 * \param[in] surfaceId The ID of the surface
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_surfaceRemoveNativeContent(t_ilm_surface surfaceId);

/**
 * \brief Set the area of a surface which should be used for the rendering.
 * \ingroup ilmClient
 * \param[in] surfaceId Id of surface.
 * \param[in] x horizontal start position of the used area
 * \param[in] y vertical start position of the used area
 * \param[in] width width of the area
 * \param[in] height height of the area
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_surfaceSetSourceRectangle(t_ilm_surface surfaceId, t_ilm_int x, t_ilm_int y, t_ilm_int width, t_ilm_int height);

/**
 * \brief Set from which kind of devices the surface can accept input events.
 * By default, a surface accept input events from all kind of devices (keyboards, pointer, ...)
 * By calling this function, you can adjust surface preferences. Note that this function only
 * adjust the acceptance for the specified devices. Non specified are keept untouched.
 * 
 * Typicall use case for this function is when dealing with pointer or touch events.
 * Those are normally dispatched to the first visible surface below the coordinate.
 * If you want a different behavior (i.e. forward events to an other surface below the coordinate,
 * you can set all above surfaces to refuse input events)
 *
 * \ingroup ilmClient
 * \param[in] surfaceId Identifier of the surface to set the keyboard focus on.
 * \param[in] devices Bitmask of ilmInputDevice
 * \param[in] acceptance Indicate if the surface accept or reject input events from the specified devices
 *
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_UpdateInputEventAcceptanceOn(t_ilm_surface surfaceId, ilmInputDevice devices, t_ilm_bool acceptance);

/**
 * \brief register for notification on property changes of surface
 * \ingroup ilmClient
 * \param[in] surface id of surface to register for notification
 * \param[in] callback pointer to function to be called for notification
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 * \return ILM_ERROR_INVALID_ARGUMENT if the given surface already has notification callback registered
 */
ilmErrorTypes ilm_surfaceAddNotification(t_ilm_surface surface, surfaceNotificationFunc callback);

/**
 * \brief remove notification on property changes of surface
 * \ingroup ilmClient
 * \param[in] surface id of surface to remove notification
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 * \return ILM_ERROR_INVALID_ARGUMENT if the given surface has no notification callback registered
 */
ilmErrorTypes ilm_surfaceRemoveNotification(t_ilm_surface surface);

/**
 * \brief Get the visibility of a surface. If a surface is not visible, the surface
 * will not be rendered.
 * \ingroup ilmClient
 * \param[in] surfaceId Id of the surface to get the visibility of.
 * \param[out] pVisibility pointer where the visibility of a surface should be stored
 *                         ILM_SUCCESS if the surface is visible,
 *                         ILM_FALSE if the visibility is disabled.
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_surfaceGetVisibility(t_ilm_surface surfaceId, t_ilm_bool *pVisibility);

/**
 * \brief Get the horizontal and vertical dimension of the surface.
 * \ingroup ilmClient
 * \param[in] surfaceId Id of surface.
 * \param[out] pDimension pointer to an array where the dimension should be stored.
 *                        dimension[0]=width, dimension[1]=height
 *
 *
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_surfaceGetDimension(t_ilm_surface surfaceId, t_ilm_uint *pDimension);

/**
 * \brief Get the surface properties from the Layermanagement
 * \ingroup ilmClient
 * \param[in] surfaceID surface Indentifier as a Number from 0 .. MaxNumber of Surfaces
 * \param[out] pSurfaceProperties pointer where the surface properties should be stored
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not get the resolution.
 */
ilmErrorTypes ilm_getPropertiesOfSurface(t_ilm_uint surfaceID, struct ilmSurfaceProperties* pSurfaceProperties);

/**
 * \brief Add a surface to a layer which is currently managed by the service
 * \ingroup ilmClient
 * \param[in] layerId Id of layer which should host the surface.
 * \param[in] surfaceId Id of surface which should be added to the layer.
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_layerAddSurface(t_ilm_layer layerId, t_ilm_surface surfaceId);

/**
 * \brief Removes a surface from a layer which is currently managed by the service
 * \ingroup ilmClient
 * \param[in] layerId Id of the layer which contains the surface.
 * \param[in] surfaceId Id of the surface which should be removed from the layer.
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_layerRemoveSurface(t_ilm_layer layerId, t_ilm_surface surfaceId);

/**
 * \brief Commit all changes and executed commands since last commit.
 * \ingroup ilmClient
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_commitChanges();

/* BEGIN OF CONTROL API */

/**
 * \brief  Get the layer properties from the Layermanagement
 * \ingroup ilmControl
 * \param[in] layerID layer Indentifier as a Number from 0 .. MaxNumber of Layer
 * \param[out] pLayerProperties pointer where the layer properties should be stored
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not get the resolution.
 */
ilmErrorTypes ilm_getPropertiesOfLayer(t_ilm_uint layerID, struct ilmLayerProperties* pLayerProperties);

/**
 * \brief  Get the number of hardware layers of a screen
 * \ingroup ilmControl
 * \param[in] screenID id of the screen, where the number of Hardware Layers should be returned
 * \param[out] pNumberOfHardwareLayers pointer where the number of hardware layers should be stored
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not get the resolution.
 */
ilmErrorTypes ilm_getNumberOfHardwareLayers(t_ilm_uint screenID, t_ilm_uint* pNumberOfHardwareLayers);

/**
 * \brief Get the screen Ids
 * \ingroup ilmControl
 * \param[out] pNumberOfIDs pointer where the number of Screen Ids should be returned
 * \param[out] ppIDs pointer to array where the IDs should be stored
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not get the resolution.
 */
ilmErrorTypes ilm_getScreenIDs(t_ilm_uint* pNumberOfIDs, t_ilm_uint** ppIDs);

/**
 * \brief Get all LayerIds which are currently registered and managed by the services
 * \ingroup ilmControl
 * \param[out] pLength Pointer where length of ids array should be stored
 * \param[out] ppArray Array where the ids should be stored,
 *                     the array will be allocated inside
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_getLayerIDs(t_ilm_int* pLength,t_ilm_layer** ppArray);

/**
 * \brief Get all LayerIds of the given screen
 * \ingroup ilmControl
 * \param[in] screenID The id of the screen to get the layer IDs of
 * \param[out] pLength Pointer where length of ids array should be stored
 * \param[out] ppArray Array where the ids should be stored,
 *                     the array will be allocated inside
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_getLayerIDsOnScreen(t_ilm_uint screenID, t_ilm_int* pLength,t_ilm_layer** ppArray);

/**
 * \brief Get all SurfaceIDs which are currently registered and managed by the services
 * \ingroup ilmControl
 * \param[out] pLength Pointer where length of ids array should be stored
 * \param[out] ppArray Array where the ids should be stored,
 *                     the array will be allocated inside
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_getSurfaceIDs(t_ilm_int* pLength,t_ilm_surface** ppArray);

/**
 * \brief Get all SurfaceIds which are currently registered to a given layer and are managed by the services
 * \ingroup ilmControl
 * \param[in] layer Id of the Layer whose surfaces are to be returned
 * \param[out] pLength Pointer where the array length of ids should be stored
 * \param[out] ppArray Array where the surface id should be stored,
 *                     the array will be allocated inside
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_getSurfaceIDsOnLayer(t_ilm_layer layer,t_ilm_int* pLength,t_ilm_surface** ppArray);

/**
 * \brief Create a layer which should be managed by the service
 * \deprecated Will be removed in later version please use ilm_layerCreateWithDimension
 * \ingroup ilmControl
 * \param[out] pLayerId pointer where the id should be/is stored. It is possible
 *                      to set a id from outside, 0 will create a new id.
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_layerCreate(t_ilm_layer* pLayerId);

/**
 * \brief Create a layer which should be managed by the service
 * \ingroup ilmControl
 * \param[out] pLayerId pointer where the id should be/is stored. It is possible
 *                      to set a id from outside, 0 will create a new id.
  *\param[in] width     horizontal dimension of the layer
 *  
 * \param[in] height    vertical dimension of the layer
 *                      
* 
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_layerCreateWithDimension(t_ilm_layer* pLayerId, t_ilm_uint width, t_ilm_uint height);

/**
 * \brief Removes a layer which is currently managed by the service
 * \ingroup ilmControl
 * \param[in] layerId Layer to be removed
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_layerRemove(t_ilm_layer layerId);

/**
 * \brief Get the current type of the layer.
 * \ingroup ilmControl
 * \param[in] layerId Id of the layer.
 * \param[out] pLayerType pointer to the layerType where the result should be stored.
 * \note ilmLayerType for information on supported types
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_layerGetType(t_ilm_layer layerId, ilmLayerType* pLayerType);

/**
 * \brief Set the visibility of a layer. If a layer is not visible, the layer and its
 * surfaces will not be rendered.
 * \ingroup ilmControl
 * \param[in] layerId Id of the layer.
 * \param[in] newVisibility ILM_SUCCESS sets layer visible, ILM_FALSE disables the visibility.
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_layerSetVisibility(t_ilm_layer layerId, t_ilm_bool newVisibility);

/**
 * \brief Get the visibility of a layer. If a layer is not visible, the layer and its
 * surfaces will not be rendered.
 * \ingroup ilmControl
 * \param[in] layerId Id of layer.
 * \param[out] pVisibility pointer where the visibility of the layer should be stored
 *                         ILM_SUCCESS if the Layer is visible,
 *                         ILM_FALSE if the visibility is disabled.
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_layerGetVisibility(t_ilm_layer layerId,t_ilm_bool *pVisibility);

/**
 * \brief Set the opacity of a layer.
 * \ingroup ilmControl
 * \param[in] layerId Id of the layer.
 * \param[in] opacity 0.0 means the layer is fully transparent,
 *                    1.0 means the layer is fully opaque
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_layerSetOpacity(t_ilm_layer layerId, t_ilm_float opacity);

/**
 * \brief Get the opacity of a layer.
 * \ingroup ilmControl
 * \param[in] layerId Id of the layer to obtain the opacity of.
 * \param[out] pOpacity pointer where the layer opacity should be stored.
 *                      0.0 means the layer is fully transparent,
 *                      1.0 means the layer is fully opaque
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_layerGetOpacity(t_ilm_layer layerId, t_ilm_float *pOpacity);

/**
 * \brief Set the area of a layer which should be used for the rendering. Only this part will be visible.
 * \ingroup ilmControl
 * \param[in] layerId Id of the layer.
 * \param[in] x horizontal start position of the used area
 * \param[in] y vertical start position of the used area
 * \param[in] width width of the area
 * \param[in] height height of the area
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_layerSetSourceRectangle(t_ilm_layer layerId, t_ilm_uint x, t_ilm_uint y, t_ilm_uint width, t_ilm_uint height);

/**
 * \brief Set the destination area on the display for a layer. The layer will be scaled and positioned to this rectangle for rendering
 * \ingroup ilmControl
 * \param[in] layerId Id of the layer.
 * \param[in] x horizontal start position of the used area
 * \param[in] y vertical start position of the used area
 * \param[in] width width of the area
 * \param[in] height height of the area
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_layerSetDestinationRectangle(t_ilm_layer layerId, t_ilm_int x, t_ilm_int y, t_ilm_int width, t_ilm_int height);

/**
 * \brief Get the horizontal and vertical dimension of the layer.
 * \ingroup ilmControl
 * \param[in] layerId Id of layer.
 * \param[out] pDimension pointer to an array where the dimension should be stored.
 *                       dimension[0]=width, dimension[1]=height
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_layerGetDimension(t_ilm_layer layerId, t_ilm_uint *pDimension);

/**
 * \brief Set the horizontal and vertical dimension of the layer.
 * \ingroup ilmControl
 * \param[in] layerId Id of layer.
 * \param[in] pDimension pointer to an array where the dimension is stored.
 *                       dimension[0]=width, dimension[1]=height
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_layerSetDimension(t_ilm_layer layerId, t_ilm_uint *pDimension);

/**
 * \brief Get the horizontal and vertical position of the layer.
 * \ingroup ilmControl
 * \param[in] layerId Id of layer.
 * \param[out] pPosition pointer to an array where the position should be stored.
 *                       dimension[0]=width, dimension[1]=height
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_layerGetPosition(t_ilm_layer layerId, t_ilm_uint *pPosition);

/**
 * \brief Sets the horizontal and vertical position of the layer.
 * \ingroup ilmControl
 * \param[in] layerId Id of layer.
 * \param[in] pPosition pointer to an array where the position is stored.
 *                      dimension[0]=x, dimension[1]=y
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_layerSetPosition(t_ilm_layer layerId, t_ilm_uint *pPosition);

/**
 * \brief Sets the orientation of a layer.
 * \ingroup ilmControl
 * \param[in] layerId Id of layer.
 * \param[in] orientation Orientation of the layer.
 * \note ilmOrientation for more information on orientation values
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_layerSetOrientation(t_ilm_layer layerId, ilmOrientation orientation);

/**
 * \brief Gets the orientation of a layer.
 * \ingroup ilmControl
 * \param[in] layerId Id of layer.
 * \param[out] pOrientation Address where orientation of the layer should be stored.
 * \note ilmOrientation for more information on orientation values
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_layerGetOrientation(t_ilm_layer layerId, ilmOrientation *pOrientation);

/**
 * \brief Sets the color value which defines the transparency value.
 * \ingroup ilmControl
 * \param[in] layerId Id of layer.
 * \param[in] pColor array of the color value which is defined in red,green, blue
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_layerSetChromaKey(t_ilm_layer layerId, t_ilm_int* pColor);

/**
 * \brief Sets render order of surfaces within one layer
 * \ingroup ilmControl
 * \param[in] layerId Id of layer.
 * \param[in] pSurfaceId array of surface ids
 * \param[in] number Number of elements in the given array of ids
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_layerSetRenderOrder(t_ilm_layer layerId, t_ilm_layer *pSurfaceId, t_ilm_int number);

/**
 * \brief Get the capabilities of a layer
 * \ingroup ilmControl
 * \param[in] layerId Id of the layer to obtain the capabilities of
 * \param[out] pCapabilities The address where the capabilites are returned
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_layerGetCapabilities(t_ilm_layer layerId, t_ilm_layercapabilities *pCapabilities);

/**
 * \brief Get the possible capabilities of a layertype
 * \ingroup ilmControl
 * \param[in] layerType The layertype to obtain the capabilities of
 * \param[out] pCapabilities The address where the capabilites are returned
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_layerTypeGetCapabilities(ilmLayerType layerType, t_ilm_layercapabilities *pCapabilities);

/**
 * \brief Create the logical surface, which has no native buffer associated
 * \ingroup ilmControl
 * \param[in] pSurfaceId The value pSurfaceId points to is used as ID for new surface;
 * \param[out] pSurfaceId The ID of the newly created surface is returned in this parameter
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_surfaceInitialize(t_ilm_surface *pSurfaceId);

/**
 * \brief Set the visibility of a surface. If a surface is not visible it will not be rendered.
 * \ingroup ilmControl
 * \param[in] surfaceId Id of the surface to set the visibility of
 * \param[in] newVisibility ILM_SUCCESS sets surface visible, ILM_FALSE disables the visibility.
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_surfaceSetVisibility(t_ilm_surface surfaceId, t_ilm_bool newVisibility);

/**
 * \brief Set the opacity of a surface.
 * \ingroup ilmControl
 * \param surfaceId Id of the surface to set the opacity of.
 * \param opacity 0.0 means the surface is fully transparent,
 *                1.0 means the surface is fully opaque
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_surfaceSetOpacity(const t_ilm_surface surfaceId, t_ilm_float opacity);

/**
 * \brief Get the opacity of a surface.
 * \ingroup ilmControl
 * \param[in] surfaceId Id of the surface to get the opacity of.
 * \param[out] pOpacity pointer where the surface opacity should be stored.
 *                      0.0 means the surface is fully transparent,
 *                      1.0 means the surface is fully opaque
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_surfaceGetOpacity(const t_ilm_surface surfaceId, t_ilm_float *pOpacity);

/**
 * \brief Set the keyboard focus on a certain surface
 * To receive keyboard events, 2 conditions must be fulfilled:
 *  1- The surface must accept events from keyboard. See ilm_UpdateInputEventAcceptanceOn
 *  2- The keyboard focus must be set on that surface
 * 
 * \ingroup ilmControl
 * \param[in] surfaceId Identifier of the surface to set the keyboard focus on.
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_SetKeyboardFocusOn(t_ilm_surface surfaceId);

/**
 * \brief Get the indentifier of the surface which hold the keyboard focus
 * 
 * \ingroup ilmControl
 * \param[out] pSurfaceId Pointer on the a surface identifier
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_GetKeyboardFocusSurfaceId(t_ilm_surface* pSurfaceId);

/**
 * \brief Set the destination area of a surface within a layer for rendering. The surface will be scaled to this rectangle for rendering.
 * \ingroup ilmControl
 * \param[in] surfaceId Id of surface.
 * \param[in] x horizontal start position of the used area
 * \param[in] y vertical start position of the used area
 * \param[in] width width of the area
 * \param[in] height height of the area
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_surfaceSetDestinationRectangle(t_ilm_surface surfaceId, t_ilm_int x, t_ilm_int y, t_ilm_int width, t_ilm_int height);

/**
 * \brief Set the horizontal and vertical dimension of the surface.
 * \ingroup ilmControl
 * \param[in] surfaceId Id of surface.
 * \param[in] pDimension pointer to an array where the dimension is stored.
 *                       dimension[0]=width, dimension[1]=height
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_surfaceSetDimension(t_ilm_surface surfaceId, t_ilm_uint *pDimension);

/**
 * \brief Get the horizontal and vertical position of the surface.
 * \ingroup ilmControl
 * \param[in] surfaceId Id of surface.
 * \param[out] pPosition pointer to an array where the position should be stored.
 *                       position[0]=x, position[1]=y
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_surfaceGetPosition(t_ilm_surface surfaceId, t_ilm_uint *pPosition);

/**
 * \brief Sets the horizontal and vertical position of the surface.
 * \ingroup ilmControl
 * \param[in] surfaceId Id of surface.
 * \param[in] pPosition pointer to an array where the position is stored.
 *                      position[0]=x, position[1]=y
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_surfaceSetPosition(t_ilm_surface surfaceId, t_ilm_uint *pPosition);

/**
 * \brief Sets the orientation of a surface.
 * \ingroup ilmControl
 * \param[in] surfaceId Id of surface.
 * \param[in] orientation Orientation of the surface.
 * \note ilmOrientation for information about orientation values
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_surfaceSetOrientation(t_ilm_surface surfaceId, ilmOrientation orientation);

/**
 * \brief Gets the orientation of a surface.
 * \ingroup ilmControl
 * \param[in]  surfaceId Id of surface.
 * \param[out] pOrientation Address where orientation of the surface should be stored.
 * \note ilmOrientation for information about orientation values
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_surfaceGetOrientation(t_ilm_surface surfaceId, ilmOrientation *pOrientation);

/**
 * \brief Gets the pixelformat of a surface.
 * \ingroup ilmControl
 * \param[in] surfaceId Id of surface.
 * \param[out] pPixelformat Pointer where the pixelformat of the surface should be stored
 * \note ilmPixelFormat for information about pixel format values
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_surfaceGetPixelformat(t_ilm_layer surfaceId, ilmPixelFormat *pPixelformat);

/**
 * \brief Sets the color value which defines the transparency value of a surface.
 * \ingroup ilmControl
 * \param[in] surfaceId Id of the surface to set the chromakey of.
 * \param[in] pColor array of the color value which is defined in red, green, blue
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_surfaceSetChromaKey(t_ilm_surface surfaceId, t_ilm_int* pColor);

/**
 * \brief Sets render order of layers on a display
 * \ingroup ilmControl
 * \param[in] display Id of display to set the given order of layers.
 * \param[in] pLayerId array of layer ids
 * \param[in] number number of layerids in the given array
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_displaySetRenderOrder(t_ilm_display display, t_ilm_layer *pLayerId, const t_ilm_uint number);

/**
 * \brief Take a screenshot from the current displayed layer scene.
 * The screenshot is saved as bmp file with the corresponding filename.
 * \ingroup ilmControl
 * \param[in] screen Id of screen where screenshot should be taken
 * \param[in] filename Location where the screenshot should be stored
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_takeScreenshot(t_ilm_uint screen, t_ilm_const_string filename);

/**
 * \brief Take a screenshot of a certain layer
 * The screenshot is saved as bmp file with the corresponding filename.
 * \ingroup ilmControl
 * \param[in] filename Location where the screenshot should be stored
 * \param[in] layerid Identifier of the layer to take the screenshot of
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_takeLayerScreenshot(t_ilm_const_string filename, t_ilm_layer layerid);

/**
 * \brief Take a screenshot of a certain surface
 * The screenshot is saved as bmp file with the corresponding filename.
 * \ingroup ilmControl
 * \param[in] filename Location where the screenshot should be stored
 * \param[in] surfaceid Identifier of the surface to take the screenshot of
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_takeSurfaceScreenshot(t_ilm_const_string filename, t_ilm_surface surfaceid);


/**
 * \brief Enable or disable a rendering optimization
 *
 * \ingroup ilmControl
 * \param[in] id which optimization to change
 * \param[in] mode the mode to set on the optimzation (e.g. ON, OFF, AUTO)
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_SetOptimizationMode(ilmOptimization id, ilmOptimizationMode mode);

/**
 * \brief Get the current enablement for an optimization
 *
 * \ingroup ilmControl
 * \param[in] id which optimization to query
 * \param[out] mode current optimization mode
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 */
ilmErrorTypes ilm_GetOptimizationMode(ilmOptimization id, ilmOptimizationMode* mode);

/**
 * \brief register for notification on property changes of layer
 * \ingroup ilmControl
 * \param[in] layer id of layer to register for notification
 * \param[in] callback pointer to function to be called for notification
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 * \return ILM_ERROR_INVALID_ARGUMENT if the given layer already has notification callback registered
 */
ilmErrorTypes ilm_layerAddNotification(t_ilm_layer layer, layerNotificationFunc callback);

/**
 * \brief remove notification on property changes of layer
 * \ingroup ilmControl
 * \param[in] layer id of layer to remove notification
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not call the method on the service.
 * \return ILM_ERROR_INVALID_ARGUMENT if the given layer has no notification callback registered
 */
ilmErrorTypes ilm_layerRemoveNotification(t_ilm_layer layer);

/**
 * \brief Get the screen properties from the Layermanagement
 * \ingroup ilmClient
 * \param[in] screenID screen Indentifier
 * \param[out] pScreenProperties pointer where the screen properties should be stored
 * \return ILM_SUCCESS if the method call was successful
 * \return ILM_FAILED if the client can not get the resolution.
 */
ilmErrorTypes ilm_getPropertiesOfScreen(t_ilm_display screenID, struct ilmScreenProperties* pScreenProperties);

#ifdef __cplusplus
} //
#endif // __cplusplus

#endif /* _ILM_CLIENT_H_ */


