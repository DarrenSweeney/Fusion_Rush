#if !defined(_GS_LINKING_HPP_)
#	define _GS_LINKING_HPP_
#	if !defined(GS_API)
#		if PLATFORM_WINDOWS && !IS_MONOLITHIC// we're building a dll on UE4 windows
#			if defined(GS_BUILDING_MODULE) // as opposed to using the dll
#				define GS_API __declspec( dllexport )
#			else /* defined(GS_BUILDING_MODULE) */
#				define GS_API __declspec( dllimport )
#			endif /* defined(GS_BUILDING_MODULE) */
#		else /* PLATFORM_WINDOWS */
#			define GS_API
#		endif /* PLATFORM_WINDOWS */
#	endif /* !defined(GS_API) */
#endif /* _GS_LINKING_HPP_ */
