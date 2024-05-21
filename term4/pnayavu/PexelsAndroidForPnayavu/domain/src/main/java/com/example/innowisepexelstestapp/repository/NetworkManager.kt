package com.example.innowisepexelstestapp.repository

import com.example.innowisepexelstestapp.model.Category
import com.example.innowisepexelstestapp.model.PhotoPexels
import io.reactivex.Single

interface NetworkManager {
    fun getCuratedPhotos(): Single<List<PhotoPexels>>

    fun getQueryPhotos(query: String): Single<List<PhotoPexels>>

    fun getCategories(): Single<List<Category>>

}