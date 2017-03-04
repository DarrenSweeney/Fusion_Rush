#if !defined(_GS_LINKING_HPP_)
#	define _GS_LINKING_HPP_
#	if !defined(GS_API)
#		if PLATFORM_WINDOWS // we're building a dll on UE4 windows
#			if defined(GS_BUILDING_DLL) // as opposed to using the dll
#				define GS_API __declspec( dllexport )
#			else /* defined(GS_BUILDING_DLL) */
#				define GS_API __declspec( dllimport )
#			endif /* defined(GS_BUILDING_DLL) */
#		else /* PLATFORM_WINDOWS */
#			define GS_API
#		endif /* PLATFORM_WINDOWS */
#	endif /* !defined(GS_API) */
#endif /* _GS_LINKING_HPP_ */
