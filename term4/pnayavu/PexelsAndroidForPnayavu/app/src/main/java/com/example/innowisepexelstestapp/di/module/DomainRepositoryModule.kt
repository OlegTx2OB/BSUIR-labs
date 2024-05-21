package com.example.innowisepexelstestapp.di.module

import android.content.Context
import com.example.innowisepexelstestapp.repository.DownloadFilesManager
import com.example.innowisepexelstestapp.repository.FavoritePhotoManager
import com.example.innowisepexelstestapp.repository.NetworkManager
import com.example.innowisepexelstestapp.repository.downloadmanager.DownloadFilesManagerImpl
import com.example.innowisepexelstestapp.repository.pexelsapi.NetworkManagerImpl
import com.example.innowisepexelstestapp.repository.pexelsapi.PexelsNetworkClient
import com.example.innowisepexelstestapp.repository.room.FavoritePhotoManagerImpl
import com.example.innowisepexelstestapp.repository.room.PhotoPexelsDao
import dagger.Module
import dagger.Provides
import javax.inject.Singleton

@Module
class DomainRepositoryModule {

    @Singleton
    @Provides
    fun provideNetworkManagerImpl(networkClient: PexelsNetworkClient): NetworkManager {
        return NetworkManagerImpl(networkClient)
    }

    @Singleton
    @Provides
    fun provideFavoritePhotoManager(photoPexelsDao: PhotoPexelsDao): FavoritePhotoManager {
        return FavoritePhotoManagerImpl(photoPexelsDao)
    }

    @Singleton
    @Provides
    fun provideDownloadFilesManager(mAppContext: Context): DownloadFilesManager {
        return DownloadFilesManagerImpl(mAppContext)
    }

}