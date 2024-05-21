package com.example.innowisepexelstestapp.usecase

import com.example.innowisepexelstestapp.model.PhotoPexels
import com.example.innowisepexelstestapp.repository.FavoritePhotoManager

class DeleteImageFromRoomUseCase(private val favoritePhotoManager: FavoritePhotoManager) {
    fun execute(photoPexels: PhotoPexels) {
        favoritePhotoManager.deleteFavoritePhoto(photoPexels)
    }
}