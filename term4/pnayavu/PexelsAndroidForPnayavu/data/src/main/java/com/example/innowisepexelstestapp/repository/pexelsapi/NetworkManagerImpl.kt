package com.example.innowisepexelstestapp.repository.pexelsapi

import android.util.Log
import com.example.innowisepexelstestapp.dto.CategoryDto
import com.example.innowisepexelstestapp.dto.CollectionsResultDto
import com.example.innowisepexelstestapp.dto.CuratedResultDto
import com.example.innowisepexelstestapp.dto.PhotoPexelsDto
import com.example.innowisepexelstestapp.mapper.CategoryMapper
import com.example.innowisepexelstestapp.mapper.PhotoPexelsMapper
import com.example.innowisepexelstestapp.model.Category
import com.example.innowisepexelstestapp.model.PhotoPexels
import com.example.innowisepexelstestapp.repository.NetworkManager
import com.google.gson.Gson
import com.google.gson.reflect.TypeToken
import io.reactivex.Single
import io.reactivex.schedulers.Schedulers

class NetworkManagerImpl(private val mNetworkClient: PexelsNetworkClient) : NetworkManager {

    private val mPhotoMapper = PhotoPexelsMapper()
    private val mCategoryMapper = CategoryMapper()

    override fun getCuratedPhotos(): Single<List<PhotoPexels>> {
        return Single.fromCallable {
            val response = mNetworkClient.getResponseWithCuratedPhotos()
            Log.wtf("iiy", response.toString())
            if (!response.isSuccessful) {
                //todo мб иначе обработать
                throw Exception("Failed to get curated photos")
            }

            val curatedResultDto: List<PhotoPexelsDto> = Gson().fromJson<List<PhotoPexelsDto>>(
                response.body?.string(),
                object : TypeToken<List<PhotoPexelsDto>>() {}.type
            )
            return@fromCallable mPhotoMapper.toModels(curatedResultDto)
        }.subscribeOn(Schedulers.computation())
    }

    override fun getCategories(): Single<List<Category>> {
        return Single.fromCallable {
            val response = mNetworkClient.getResponseWithFeaturedCategories()
            if (!response.isSuccessful) {
                //todo мб иначе обработать
                throw Exception("Failed to get curated photos")
            }
            val collectionsResultDto: List<CategoryDto> = Gson().fromJson<List<CategoryDto>>(
                response.body?.string(),
                object : TypeToken<List<CategoryDto>>() {}.type
            )
            return@fromCallable mCategoryMapper.toModels(collectionsResultDto)
        }.subscribeOn(Schedulers.computation())
    }

    override fun getQueryPhotos(query: String): Single<List<PhotoPexels>> {
        return Single.fromCallable {
            val response = mNetworkClient.getResponseWithQueryPhotos(query)
            if (!response.isSuccessful) {
                //todo мб иначе обработать
                throw Exception("Failed to get curated photos")
            }

            val curatedResultDto: CuratedResultDto = Gson().fromJson(response.body?.string(), CuratedResultDto::class.java)
            Log.wtf("pnayavu", "QUERY\n"+curatedResultDto.toString())
            return@fromCallable mPhotoMapper.toModels(curatedResultDto.photos)
        }.subscribeOn(Schedulers.computation())
    }
}