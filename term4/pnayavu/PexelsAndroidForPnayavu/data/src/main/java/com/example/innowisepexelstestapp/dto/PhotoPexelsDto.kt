package com.example.innowisepexelstestapp.dto

import androidx.room.Entity
import androidx.room.PrimaryKey
import com.google.gson.annotations.SerializedName

@Entity
data class PhotoPexelsDto(
    @PrimaryKey
    @SerializedName("id") val id: Int,
    @SerializedName("photographer") val photographer: String,
    @SerializedName("sourceDto") val sourceDto: SourceDto,
)
data class SourceDto(
    @SerializedName("id") val id: Int,
    @SerializedName("original_url") val original: String,
    @SerializedName("medium_url") val medium: String,
)