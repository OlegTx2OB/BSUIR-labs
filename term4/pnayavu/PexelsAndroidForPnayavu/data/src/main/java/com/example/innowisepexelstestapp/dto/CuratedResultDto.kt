package com.example.innowisepexelstestapp.dto

import com.google.gson.annotations.SerializedName

data class CuratedResultDto(
    @SerializedName("photoDtos") val photos: List<PhotoPexelsDto>,
)