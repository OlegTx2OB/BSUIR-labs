package com.example.innowisepexelstestapp.repository.room

import androidx.room.TypeConverter
import com.example.innowisepexelstestapp.dto.SourceDto
import com.google.gson.Gson

object ImageSourcesConverter {

    @TypeConverter
    @JvmStatic
    fun fromImageSourcesEntity(imageSources: SourceDto): String {
        return Gson().toJson(imageSources)
    }

    @TypeConverter
    @JvmStatic
    fun toImageSourcesEntity(imageSourcesString: String): SourceDto {
        return Gson().fromJson(imageSourcesString, SourceDto::class.java)
    }
}