package com.example.innowisepexelstestapp.di.module

import android.content.Context
import androidx.room.Room
import com.example.innowisepexelstestapp.repository.room.PhotoPexelsDao
import com.example.innowisepexelstestapp.repository.FavoritePhotoManager
import com.example.innowisepexelstestapp.repository.room.FavoritePhotoDataBase
import com.example.innowisepexelstestapp.repository.room.FavoritePhotoManagerImpl

import dagger.Module
import dagger.Provides
import javax.inject.Singleton

@Module
class DataRoomModule {

    @Singleton
    @Provides
    fun providePhotoPexelsDao(mAppContext: Context): PhotoPexelsDao {
        return Room.databaseBuilder(
            mAppContext, FavoritePhotoDataBase::class.java, "roomDBCategories"
        ).allowMainThreadQueries().build().photoPexelsDao()
    }

}