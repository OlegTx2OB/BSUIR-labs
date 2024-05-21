package com.example.innowisepexelstestapp.presentation.navigation

import com.example.innowisepexelstestapp.model.PhotoPexels
import com.example.innowisepexelstestapp.presentation.view.DetailsFragment
import com.example.innowisepexelstestapp.presentation.view.FavoriteFragment
import com.example.innowisepexelstestapp.presentation.view.HomeFragment
import com.example.innowisepexelstestapp.util.withArguments
import com.github.terrakok.cicerone.androidx.FragmentScreen

object Screens {
    fun homeFragment() = FragmentScreen { HomeFragment() }
    fun favoriteFragment() = FragmentScreen { FavoriteFragment() }
    fun detailsFragment(photoPexels: PhotoPexels, isItLikedPhoto: Boolean) = FragmentScreen {
        DetailsFragment().withArguments(
            "photoPexels" to photoPexels,
            "isItLikedPhoto" to isItLikedPhoto
        )
    }
}