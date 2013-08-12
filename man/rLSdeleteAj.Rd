\name{rLSdeleteAj}
\alias{rLSdeleteAj}

\title{Delete the elements at specified rows for the specified column for the given model.}

\description{
 R interface function for LINDO API function \code{LSdeleteAj}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSdeleteAj(model,iVar1,nRows,paiRows)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{iVar1}{The index of the variable whose elements will be deleted.}
 \item{nRows}{Number of constraints at which elements will be deleted.}
 \item{paiRows}{An integer array containing the row indices of the elements to be deleted.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

