package com.example.innowisepexelstestapp.presentation.view

import android.os.Bundle
import android.view.View
import androidx.fragment.app.Fragment
import androidx.recyclerview.widget.StaggeredGridLayoutManager
import by.kirich1409.viewbindingdelegate.viewBinding
import com.example.innowisepexelstestapp.R
import com.example.innowisepexelstestapp.databinding.FragmentFavoriteBinding
import com.example.innowisepexelstestapp.di.injectViewModel
import com.example.innowisepexelstestapp.model.PhotoPexels
import com.example.innowisepexelstestapp.presentation.rv.RvPhotoAdapter
import com.example.innowisepexelstestapp.presentation.viewmodel.FavoriteViewModel

class FavoriteFragment : Fragment(R.layout.fragment_favorite), RvPhotoAdapter.ClickListener {

    private val mViewBinding by viewBinding(FragmentFavoriteBinding::bind)
    private val mViewModel: FavoriteViewModel by injectViewModel()
    private val mRvPhotoAdapter: RvPhotoAdapter = RvPhotoAdapter(this, showAuthorName = true)

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        setViewsPresets()
        mViewModel.setPhotos()
        setupListeners()
        setupObservers()
    }

    override fun onClickPhoto(photoPexels: PhotoPexels) {
        mViewModel.onClickPhoto(photoPexels)
    }

    private fun setViewsPresets() = with(mViewBinding) {
        favoriteRv.layoutManager =
            StaggeredGridLayoutManager(2, StaggeredGridLayoutManager.VERTICAL)
        favoriteRv.adapter = mRvPhotoAdapter
    }

    private fun setupListeners() = with(mViewBinding) {
        bnvHome.setOnClickListener {
            mViewModel.navigateToHome()
        }
        tvExplore.setOnClickListener {
            mViewModel.navigateToHome()
        }
    }

    private fun setupObservers() = with(mViewBinding) {
        mViewModel.ldAddPhotoList.observe(viewLifecycleOwner) {
            mRvPhotoAdapter.createNewPhotoList(it)
        }
        mViewModel.ldShowAnim.observe(viewLifecycleOwner) {
            favoriteRv.startAnimation(it)
        }
        mViewModel.ldTvNoFavoritesVisibility.observe(viewLifecycleOwner) {
            tvNoFavorites.visibility = it
        }
        mViewModel.ldTvExploreVisibility.observe(viewLifecycleOwner) {
            tvExplore.visibility = it
        }
    }

}