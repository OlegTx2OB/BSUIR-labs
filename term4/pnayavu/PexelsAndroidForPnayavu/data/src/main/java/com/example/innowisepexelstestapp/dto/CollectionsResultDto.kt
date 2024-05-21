package com.example.innowisepexelstestapp.dto

import com.google.gson.annotations.SerializedName

data class CollectionsResultDto(
    @SerializedName("collections") val collections: List<CategoryDto>,
)