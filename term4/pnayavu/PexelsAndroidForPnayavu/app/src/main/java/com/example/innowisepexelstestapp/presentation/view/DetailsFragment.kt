package com.example.innowisepexelstestapp.presentation.view

import android.os.Bundle
import android.view.View
import android.widget.Toast
import androidx.fragment.app.Fragment
import by.kirich1409.viewbindingdelegate.viewBinding
import com.example.innowisepexelstestapp.R
import com.example.innowisepexelstestapp.databinding.FragmentDetailsBinding
import com.example.innowisepexelstestapp.di.injectViewModel
import com.example.innowisepexelstestapp.model.PhotoPexels
import com.example.innowisepexelstestapp.presentation.viewmodel.DetailsViewModel
import com.example.innowisepexelstestapp.util.findArgument
import com.squareup.picasso.Picasso

class DetailsFragment : Fragment(R.layout.fragment_details) {

    private val mViewBinding by viewBinding(FragmentDetailsBinding::bind)
    private val mViewModel: DetailsViewModel by injectViewModel() //todo провериь и без injectViewModel

    private val mPhotoPexelsArg: PhotoPexels by lazy (LazyThreadSafetyMode.NONE) {
        findArgument("photoPexels")!! }
    private val mIsItLikedPhotoArg: Boolean by lazy (LazyThreadSafetyMode.NONE) {
        findArgument("isItLikedPhoto")!! }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        setupListeners()
        setViewsPresets()
        setupObservers()
    }

    private fun setViewsPresets() = with(mViewBinding) {
        authorName.text = mPhotoPexelsArg.photographer
        mViewModel.setFavoriteBtnImage(mIsItLikedPhotoArg, favoriteBtn)

        Picasso.get()
            .load(mPhotoPexelsArg.sources.original)
            .placeholder(R.drawable.ic_imagestub)
            .into(image)
    }

    private fun setupListeners() = with(mViewBinding) {
        var isItLikedPhoto = mIsItLikedPhotoArg

        favoriteBtn.setOnClickListener {
            mViewModel.onFavoriteBtn(isItLikedPhoto, favoriteBtn, mPhotoPexelsArg)
            isItLikedPhoto = !isItLikedPhoto
        }

        image.setOnViewDragListener { dx, dy ->
            if (dx != 0f || dy != 0f) {
                image.setScale(1.0f, true)
            }
        }

        downloadBtn.setOnClickListener {
            mViewModel.onDownloadBtn(mPhotoPexelsArg.sources.original)
        }
        backBtn.setOnClickListener {
            mViewModel.onBackBtn()
        }
    }

    private fun setupObservers() {
        mViewModel.ldShowToast.observe(viewLifecycleOwner) {
            Toast.makeText(requireContext(), it, Toast.LENGTH_SHORT).show()
        }
    }

}