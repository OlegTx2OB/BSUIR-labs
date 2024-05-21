package com.example.innowisepexelstestapp.repository.room

import androidx.room.Database
import androidx.room.RoomDatabase
import androidx.room.TypeConverters
import com.example.innowisepexelstestapp.dto.PhotoPexelsDto

@Database(entities = [PhotoPexelsDto::class], version = 1)
@TypeConverters(ImageSourcesConverter::class)
abstract class FavoritePhotoDataBase : RoomDatabase() {
    abstract fun photoPexelsDao(): PhotoPexelsDao
}