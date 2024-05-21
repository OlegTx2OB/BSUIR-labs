package com.example.innowisepexelstestapp.repository

import com.example.innowisepexelstestapp.model.PhotoPexels
import io.reactivex.Single

interface FavoritePhotoManager {

    fun getAllFavoritePhoto(): List<PhotoPexels>

    fun insertFavoritePhoto(photoPexels: PhotoPexels)

    fun deleteFavoritePhoto(photoPexels: PhotoPexels)
}