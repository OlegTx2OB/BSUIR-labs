package com.example.innowisepexelstestapp.repository.room

import com.example.innowisepexelstestapp.mapper.PhotoPexelsMapper
import com.example.innowisepexelstestapp.model.PhotoPexels
import com.example.innowisepexelstestapp.repository.FavoritePhotoManager

class FavoritePhotoManagerImpl(private val photoPexelsDao: PhotoPexelsDao) : FavoritePhotoManager {

    private val mMapper = PhotoPexelsMapper()
    override fun getAllFavoritePhoto(): List<PhotoPexels> { //todo добавить single
        return mMapper.toModels(photoPexelsDao.getAllPhotoPexels())
    }

    override fun insertFavoritePhoto(photoPexels: PhotoPexels) {
        photoPexelsDao.insertPhotoPexels(mMapper.toDto(photoPexels))
    }

    override fun deleteFavoritePhoto(photoPexels: PhotoPexels) {
        photoPexelsDao.deletePhotoPexels(mMapper.toDto(photoPexels))
    }
}