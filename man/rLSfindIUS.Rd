\name{rLSfindIUS}
\alias{rLSfindIUS}

\title{Find an irreducibly unbounded set (IUS) of columns for an unbounded linear program.}

\description{
 R interface function for LINDO API function \code{LSfindIUS}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSfindIUS(model,nLevel)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nLevel}{The level of analysis in finding the IUS. Bit mask values are:
                 \itemize{            
                    \item{LS_NECESSARY_COLS} { = 2}
                    \item{LS_SUFFICIENT_COLS} { = 8}
                  }
               }
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
