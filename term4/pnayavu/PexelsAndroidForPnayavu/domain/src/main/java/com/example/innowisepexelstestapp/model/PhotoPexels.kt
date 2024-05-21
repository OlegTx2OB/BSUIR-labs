package com.example.innowisepexelstestapp.model

import com.google.gson.annotations.SerializedName
import java.io.Serializable

data class PhotoPexels(
    val id: Int,
    val photographer: String,
    val sources: Source,
) : Serializable

data class Source(
    val id: Int,
    val original: String,
    val medium: String,
) : Serializable
